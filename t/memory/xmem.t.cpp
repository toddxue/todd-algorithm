#include "TAP.h"
#include "timed.h"
#include <unistd.h>

int gc, gd;
int main(int argc, char* argv[]) {

#if 0
    int n = argv[1] ? strtol(argv[1], 0, 10) : 1000;
    int c = argv[1] && argv[2] ? strtol(argv[2], 0, 10) : 10;

    for (int i = 0; i < c; ++i) {
        if ((void*)-1 == sbrk(n)) {
            printf("sbrk failed\n");
            exit(1);
        }
        else 
            printf("sbrk succeeded %d\n", n);
    }
    return 0;
#endif
    
    OK_SUM();
    
    struct M {
        size_t begin;
        size_t curr;
        M() { 
            begin = *g_xmem_pmalloced_size;
        }
        int size() { 
            curr = *g_xmem_pmalloced_size;
            return curr-begin;
        }
    };
    {
        M m;
        int* a = new int;
        delete a;
        int* b = new int;
        delete b;
        OK(m.size() == sizeof(int) + sizeof(void*));
        OK(a == b);
    }
    {
        M m;
        int* a = new int[2];
        delete[] a;
        int* b = new int[2];
        delete[] b;
        OK(m.size() == sizeof(int)*2 + sizeof(void*));
        OK(a == b);
    }

    {
        M m;
        int* a1 = new int;
        delete a1;
        int* a2 = new int[2];
        delete[] a2;

        int* b1 = new int;
        delete b1;
        int* b2 = new int[2];
        delete[] b2;

        OK(m.size() == 0);
        OK(a1 == b1 && a2 == b2);
    }

    {
        M m;
        int* a = (int*)malloc(sizeof(int));
        free(a);
        int* b = (int*)malloc(sizeof(int));
        free(b);
        OK(m.size() == 0);
        OK(a == b);
    }

    {
        M m;
        int* a = (int*)malloc(sizeof(int)*2);
        free(a);
        int* b = (int*)malloc(sizeof(int)*2);
        free(b);
        OK(m.size() == 0);
        OK(a == b);
    }

    {
        M m;
        int* a1 = (int*)malloc(sizeof(int));
        free(a1);
        int* a2 = (int*)malloc(sizeof(int)*2);
        free(a2);

        int* b1 = (int*)malloc(sizeof(int));
        free(b1);
        int* b2 = (int*)malloc(sizeof(int)*2);
        free(b2);

        OK(m.size() == 0);
        OK(a1 == b1 && a2 == b2);
    }

    // dtor called correctly after overload ::operator new/delete?
    {
        struct A {
            int& ctor_c;
            int& dtor_c;
            A(int& ctor_c, int& dtor_c) : ctor_c(ctor_c), dtor_c(dtor_c) { ++ctor_c; }
            ~A() { ++dtor_c; }
        };
        int c=0, d=0;
        A* a = new A(c,d);
        delete a;
        OK(c == 1 && d == 1);
    }

    // gcc implement new[]/delete[] as:
    // when new: ptr = int + sizeof(A) + .... + sizeof(A) 
    // when delete, ptr[0] stores the object num, so know how many
    // dtor to call
    // and the pointer a is sizeof(int) greater than the malloced ptr
    {
        struct A {
            int& ctor_c;
            int& dtor_c;
            A() : ctor_c(gc), dtor_c(gd) { ++ctor_c; }
            ~A() { ++dtor_c; }
        };
        A* a = new A[10];
        delete[] a;
        OK(gc == 10 && gd == 10);
    }
    return 0;
}
