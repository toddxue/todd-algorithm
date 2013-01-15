#include <stdio.h>
#include <stdlib.h>

void make_factor(int n, int f)
{
    if (n < f)
        return;

    while (n % f == 0) {
        printf("%d ", f);
        n = n / f;
    }
    
    make_factor(n, f+1);
}


int main(int argc, char* argv[])
{
    if (argc == 0)
        return 0;

    int n = strtol(argv[1], 0, 10);
    if (n < 0) 
        return 0;

    make_factor(n, 2);
    printf("\n");
    return 0;
}

/**
 * It doesn't support big integer, 
 * for smaller integer, compatible with the GNU factors
 *
    $ time for i in {10000..10100}; do factor $i; done | wc -l
    101
    
    real    0m2.371s
    user    0m0.541s
    sys     0m1.658s
    
    $ time for i in {10000..10100}; do ./factors.play $i; done | wc -l
    101
    
    real    0m2.215s
    user    0m0.423s
    sys     0m1.525s
 *
 **/
