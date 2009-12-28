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

/*
 *-------------------------------------------------------------------------
 *
 * max_partial_sum_circle --
 *      same as max_partial_sum, but it's a circle now, so a[n] = a[0], ...
 *      so sum like  + ... + a[n-1] + a[0] + ... also considered
 *
 *      the 1st try is to consider the array as (a[0], ..., a[n-1], a[0], ... a[n-2])
 *      in simple words, now it's a[0..2n-2] considered
 *
 *      so 1 clever solution is:
 *        max = max_partial_sum(n, a)
 *        min = min_partial_sum(n, a), 
 *        total = a[0] + ... + a[n-1]
 *      then 
 *        max = MAX(max, total-min)
 *
 *      NOTE: what's the case of min == total? 
 *      
 *      do a stupid verify quickly now, 5 pass, actually
 *
 *-------------------------------------------------------------------------
 */
int max_partial_sum_circle(int n, int* a) {
    int max = max_partial_sum(n, a);
    int total = 0;
    for (int i = 0; i < n; ++i) total += a[i];

    for (int i = 0; i < n; ++i) a[i] = -a[i];
    int min = -max_partial_sum(n, a);
    for (int i = 0; i < n; ++i) a[i] = -a[i];
    
    if (min == total)
        return max;
    
    if (total-min > max) 
        max = total-min;
    return max;
}
