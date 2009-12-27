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
