#include "rpermut.h"

bool rpermut_begin(int n, int* a, int m, int* vs)
{
    if (m == 0)
        return false;

    for (int i = 0; i < n; ++i)
        a[i] = vs[0];
    return true;
}

bool rpermut_next(int n, int* a, int m, int* vs)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == vs[j] && j+1 < m) {
                a[i] = vs[j+1];
                for (int k = 0; k < i; ++k)
                    a[k] = vs[0];
                return true;
            }
        }
    }
    return false;
}
