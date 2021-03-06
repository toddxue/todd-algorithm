#include "rpermut.h"
#include <stdio.h>

bool rpermut_begin(size_t n, int* a, size_t m, int* vs)
{
    if (m == 0)
        return false;

    for (int i = 0; i < n; ++i)
        a[i] = vs[0];
    return true;
}

bool rpermut_next(size_t n, int* a, size_t m, int* vs)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == vs[j] && j+1 < m) {
                
                /**
                 * protection of loop
                 */
                if (a[i] == vs[j+1]) {
                    fprintf(stderr, "loop detected due to bad input\n");
                    return false;
                }

                a[i] = vs[j+1];
                for (int k = 0; k < i; ++k)
                    a[k] = vs[0];
                return true;
            }
        }
    }
    return false;
}
