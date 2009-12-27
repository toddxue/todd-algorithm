/*
 * max.h --
 *
 * algorithms related to the calculation of the maximum 
 *
 * 2009/12/26: initial release by Todd Xue
 */

#ifndef _max_h
#define _max_h

/* maximum of c integers */
int max(int c, ...);

/* max{ a_i + .. a_j | 0 <= i < j < n} */
int max_partial_sum(int n, int* a);

#endif
