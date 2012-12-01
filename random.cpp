#include "random.h"
#include <stdlib.h>

void random_permutation(int n, int* a)
{
    for (int i = 0; i < n-1; ++i) {

        /**
         * pick a random pos from a[i, n)
         */
        int pos = rand();
        if (pos < 0) pos = -pos;
        pos %= (n-i);

        /**
         * swap:
         * a[i] <-> a[p]
         */
        int tmp = a[i];
        a[i] = a[i + pos];
        a[i+pos] = tmp;
    }
}


/**
 * precondition: a[0, n) has no duplicate
 */
void random_subset(int n, int* a, int m, int* b)
{
    if (m == 0)
        return;

    if (n == 0)
        return;

    random_subset(n-1, a, m-1, b);
    int pos = rand();
    if (pos < 0) pos = -pos;
    pos %= n;

    int elem = a[pos];
    bool has_elem = false;
    for (int i = 0; i < m-1; ++i) {
        if (b[i] == elem) {
            has_elem = true;
            break;
        }
    }

    if (has_elem)
        elem = a[n-1];
    
    b[m-1] = elem;
}

/**
$ for i in {1..200}; do t/random/random.play -s$RANDOM -as 4 {1..5}; done | sort | uniq -c
     41 1 2 3 4
     30 1 2 3 5
     40 1 2 4 5
     46 1 3 4 5
     43 2 3 4 5
 */
