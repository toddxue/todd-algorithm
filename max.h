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

/* same as max_partial_sum, but a[n] loops to a[0] */
int max_partial_sum_circle(int n, int* a);

/* just as the function name described */
int max_common_sub_sequence(int na, int* a, int nb, int* b, int* sub);

/* max sub increase sequences */
int max_increase_sequence(int na, int* a, int* sub);
int max_increase_sequence_count(int na, int* a);

/**
 * max distance less than: max{ j-i | 0 <= i < j < n and a_i < a_j}
 * e.g.
 *   2 5 4 3 2 1
 * --> 3
 */
int max_distance_less_than_brute_force(int n, int* a);
int max_distance_less_than_linear_time(int n, int* a);

#endif
