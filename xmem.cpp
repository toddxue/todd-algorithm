#ifdef _XMEM
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
 * 2010/01/09: initial release by Todd Xue
 */

#include <unistd.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>

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

    char* begin_addr;
    char* curr_addr;

    Xmem() : heads_c(0) { begin_addr = system_memory(0); }
    
    char* system_memory(size_t size) {
        void* r = ::sbrk(size);
        if (r == (void*)-1) {
            struct rlimit rl;
            getrlimit(RLIMIT_DATA, &rl);
            fprintf(stderr, "sbrk(%u) failed: errno = %d, error = [%s], total=%u, rlim_cur=%u, rlim_max=%u\n", 
                    size, errno, strerror(errno), size + (curr_addr-begin_addr),
                    rl.rlim_cur, rl.rlim_max
                );
            exit(1);
        }
        curr_addr = (char*)r + size;
        return (char*)r;
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

void* operator new(size_t size) 
{ return g_xmem.malloc(size); }
void operator delete(void* ptr) 
{ return g_xmem.free(ptr); }
void* malloc(size_t size) 
{ return g_xmem.malloc(size); }
void free(void* ptr) 
{ g_xmem.free(ptr); }
void* calloc(size_t size, int elem_size) 
{ return g_xmem.calloc(size, elem_size); }

#endif
