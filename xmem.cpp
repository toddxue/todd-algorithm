/*
 * xmem.cpp --
 *
 * custom mem to replace libc malloc/free
 * the purpose to let ::sbrk(0) return correct 
 * memory size of the program used
 * 
 * since it's only for this purpose, we do a 
 * simplest implementation
 *
 * and intentionaly let malloc/free very slow
 * 
 * disable this by exclude it from compile, or the reverse
 * and yet no thread support now
 *
 * due to ::sbrk has some problem on some systems, we'd like
 * to use mmap instead, this way, timed.h to be changed also
 *
 * 2010/01/09: initial release by Todd Xue
 */

#include <unistd.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/mman.h>

struct Xmem {

    struct Node {
        union {
            Node* next;
            size_t size;
        };
    };
    
    struct Head {
        size_t size;
        Node* nodes;
    };

    /*
     * global allocate eHEADS_MAX * 16 = 1M
     */
    enum { eHEADS_MAX = 1024*64 }; 
    Head heads[eHEADS_MAX];
    size_t heads_c;

    Xmem() : heads_c(0), mmap_heads_c(0), malloced_size(0) {}

    
    enum { eMMAP_HEADS_MAX = 1024*64 }; 
    struct MmapHead {
        void* addr;
        size_t allocate;
        size_t curr;
    };
    MmapHead mmap_heads[eMMAP_HEADS_MAX];
    size_t mmap_heads_c;
    size_t malloced_size;
    char* system_memory(size_t size) {
        if (mmap_heads_c > 0) {
            MmapHead* mhead = &mmap_heads[mmap_heads_c];
            if (mhead->curr + size <= mhead->allocate) {
                char* r = (char*)mhead->addr + mhead->curr;
                mhead->curr += size;
                malloced_size += size;
                return r;
            }
        }
        
        if (mmap_heads_c >= eMMAP_HEADS_MAX) {
            fprintf(stderr, 
                    "mmap_heads_c(%u) >= eMMAP_HEADS_MAX(%u)x\n", 
                    mmap_heads_c, eMMAP_HEADS_MAX);
            exit(1);
        }
        
        const int cPageSize = 1<<16; // 64K
        int len = cPageSize;
        if (size > len) {
            if (size & (cPageSize-1) == 0)
                len = size;
            else
                len = (size + cPageSize-1) & ~(cPageSize-1);
        }
        void* addr = mmap(0, len, PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (addr == (void*)-1) {
            fprintf(stderr,
                    "system-memory(%d)->mmap(%d) failed due to errno=%d errstr=[%s]\n",
                    len, len, errno, strerror(errno));
            exit(1);
        }
        MmapHead* mhead = &mmap_heads[mmap_heads_c++];
        mhead->addr = addr;
        mhead->allocate = len;
        mhead->curr = size;
        malloced_size += size;
        return (char*)mhead->addr;
    }

    void* malloc(size_t size)  {
        for (size_t i = 0; i < heads_c; ++i) {
            if (heads[i].size == size) {
                Node* node = heads[i].nodes;
                if (node) {
                    heads[i].nodes = node->next;
                    node->size = size;
                }
                else {
                    node = (Node*)system_memory(sizeof(Node) + size);
                    node->size = size;
                }
                return (char*)node + sizeof(Node);
            }
        }
        Node* node = (Node*)system_memory(sizeof(Node) + size);
        node->size = size;
        return (char*)node + sizeof(Node);
    }
    void free(void* ptr) {
        Node* node = (Node*)((char*)ptr - sizeof(Node));
        size_t size = node->size;
        for (size_t i = 0; i < heads_c; ++i) {
            if (heads[i].size == size) {
                node->next = heads[i].nodes;
                heads[i].nodes = node;
                return;
            }
        }
        if (heads_c >= eHEADS_MAX) {
            fprintf(stderr, "xmem, heads_c >= %d now\n", eHEADS_MAX);
            exit(1);
        }
        Head* head = &heads[heads_c++];
        head->size = size;
        head->nodes = node;
        node->next = 0;
    }

    void* calloc(size_t size, int elem_size) {
        void* data = malloc(size * elem_size);
        memset(data, 0, size * elem_size);
        return data;
    }
};

Xmem g_xmem;
size_t* g_xmem_pmalloced_size = &g_xmem.malloced_size;

void* operator new(size_t size) 
{ return g_xmem.malloc(size); }
void operator delete(void* ptr) 
{ return g_xmem.free(ptr); }

void* xmalloc(size_t size) 
{ return g_xmem.malloc(size); }
void xfree(void* ptr) 
{ g_xmem.free(ptr); }
void* xcalloc(size_t size, int elem_size) 
{ return g_xmem.calloc(size, elem_size); }

#include "xmem.h"

