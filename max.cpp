/*
 * max.cpp --
 *
 * algorithms related to the calculation of the maximum 
 *
 * 2009/12/26: initial release by Todd Xue
 */

#include "max.h"
#include <limits.h>
#include <stdarg.h>

/*
 *-------------------------------------------------------------------------
 *
 * max --
 *      return max(a1,a2,...), the elements number are specified by 1st para
 * 
 * RETURN:
 *      maximum, or INT_MIN if c == 0
 *
 *-------------------------------------------------------------------------
 */
int max(int c, ...) {
    int m, n;
    va_list ap;

    va_start(ap, c);
    m = INT_MIN;
    for (int i = 0; i < c; ++i) {
        n = va_arg(ap, int);
        if (n > m) 
            m = n;
    }
    return m;
}

/*
 *-------------------------------------------------------------------------
 *
 * max_partial_sum --
 *      /* max{ a_i + .. a_j | 0 <= i < j < n}
 *
 * Algorithm NOTE:
 *      The algorithm is god damnly simple, and the idea is really strange
 *
 *-------------------------------------------------------------------------
 */
int max_partial_sum(int n, int* a) {
    int max = 0;
    int sum = 0;
    bool has_positive = false;
    int single_max = INT_MIN;
    int val;

    for (int i = 0; i < n; ++i) {
        val = a[i];
        sum += val;
        if (sum > max)
            max = sum;
        else if (sum < 0)
            sum = 0;

        if (!has_positive && val > 0)
            has_positive = true;

        if (!has_positive && a[i] > single_max)
            single_max = a[i];
    }

    if (!has_positive)
        max = single_max;
    
    return max;
}
