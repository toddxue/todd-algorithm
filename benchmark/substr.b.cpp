#include "timed.h"
#include "substr.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    /**
     * even -O3 added, still 3 times slower than the libc strstr
     * what's the magic of libc strstr?
     *
     * it seems KMP wins only when bound=2, and wins only 1/10
     *
     * the worse thing is KMP even don't win the above mystrstr
     * clever algorithm, wrong thing?
     * 
     * after added the pat mask into codes, it wins in non-same-charset cases !!!  
     * so finally mask algorithm wins, not KMP.
     * 
     * i guess the libc strstr using WORD to pack the 4 bytes to do comparing
     * so it's 4 times faster than the mystrstr, is it? do a test?
     */

    char* substr0(int nstr, char* str, int npat, char* pat);

    int bound = argv[1] ? strtol(argv[1], 0, 10) : 10;

    int na = 10000000;
    int npat = argv[1] && argv[2] ? strtol(argv[2], 0, 10) : 1000;
    char* a = new char[na+1];
    char* pat = new char[npat+1];

    for (int i = 0; i < 10; ++i) {

        for (int i = 0; i < na; ++i)
            a[i] = 'a' + random() % (bound+2);
        a[na] = 0;
        
        for (int i = 0; i < npat; ++i)
            pat[i] = 'b' + random() % bound;
        pat[npat] = 0;

        char const *s1, *s2, *s3;
        {
            TIMED_BLOCK_STDERR(strstr, true);
            s1 = mystrstr(a, pat);
        }
        {
            TIMED_BLOCK_STDERR(mystrstr, true);
            s2 = mystrstr(a, pat);
        }
        {
            TIMED_BLOCK_STDERR(KMP, true);
            s3 = substr(na, a, npat, pat);
        }
        if (s1 != s2 || s1 != s3) {
            fprintf(stderr, "result different for this run\n");
        }
        fprintf(stderr, "\n");
    }

    for (int i = 0; i < 10; ++i) {
        for (int i = 0; i < na; ++i)
            a[i] = 'a' + random() % bound;
        a[na] = 0;
        
        for (int i = 0; i < npat; ++i)
            pat[i] = 'a' + random() % bound;
        pat[npat] = 0;

        char const *s1, *s2, *s3;
        {
            TIMED_BLOCK_STDERR(samecharset_strstr, true);
            s1 = strstr(a, pat);
        }
        {
            TIMED_BLOCK_STDERR(samecharset_mystrstr, true);
            s2 = mystrstr(a, pat);
        }
        {
            TIMED_BLOCK_STDERR(samecharset_KMP, true);
            s3 = substr(na, a, npat, pat);
        }
        if (s1 != s2 || s1 != s3) {
            fprintf(stderr, "result different for this run\n");
        }
        fprintf(stderr, "\n");
    }
    delete[] a;
    delete[] pat;
    return 0;
}
