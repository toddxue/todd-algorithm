/*
 * sort.cpp --
 *
 * algorithms related to misc sorting 
 *
 * 2009/12/26: initial release by Todd Xue
 */

#include "sort.h"
#include <limits.h>
#include <stdarg.h>

/*
 *-------------------------------------------------------------------------
 *
 * sort_1_to_n_inplace --
 *      sort disordered 1,2,...,n without extra storage
 *
 * Algorithm note:
 *      != below return
 *         -true at most n due to each such case causes a a[j] = j
 *              and only n values of j: 0..(n-1)
 *         -false at most n times obviously
 * 
 *      It's a O(n) algorithm, but it random jump too much :(
 *      
 *-------------------------------------------------------------------------
 */
void sort_1_to_n_inplace(int n, int* a) {

    for (int i = 0; i < n; ++i) {
        while (a[i] != i) {    /* suppose a[0..(i-1)] already sorted 
                                * based on this, we have a[i] > i 
                                * if loop inside
                                */
            int j = a[i];
            int v_at_j = a[j];
            a[j] = j;
            a[i] = v_at_j;
        }
    }

}
