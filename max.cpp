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
 *      The key is to define the good segment as:
 *           a[0..n] is good if
 *              s(i) >= 0 for 0<=i<n
 *              and s(n) < 0
 *      Then we seperate the whole array into good_1 + good_2 + ... + good_n
 *      And we have:
 *            1. the max sequence can't be across good segment boundary
 *            2. the max sequence must be left anchored with the good segment
 *               This means the max sequence must be
 *                   max(s(i)) of good segment
 *
 *      After totally understand the algorithm, the codes can be written cleaner
 *      now.
 *      NOTE: most sample codes on internet doesn't handle correctly for all
 *            negative value sequences
 *
 *  Pre Condtion: n > 0
 *
 *-------------------------------------------------------------------------
 */
int max_partial_sum(int n, int* a) {
    int max = INT_MIN;
    int i = 0;

    do {
        int v = 0;
        do {
            v += a[i++];
            if (v > max) max = v;
        }
        while (v >= 0 && i < n);
    }
    while (i < n);

    return max;
}

