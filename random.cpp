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

