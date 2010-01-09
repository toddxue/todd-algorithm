#include "TAP.h"
#include <unistd.h>

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
    
#if defined(_XMEM)
    OK_SUM();
    
    struct M {
        char* addr;
        char* curr;
        M() { 
            addr = (char*)::sbrk(0); 
        }
        int size() { 
            curr = (char*)::sbrk(0); 
            return int(curr-addr);
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
#else
    printf("1..1\n");
    printf("ok 1 - _XMEM not defined");
#endif
    return 0;
}
