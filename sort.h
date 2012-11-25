/*
 * sort.h --
 *
 * algorithms related to misc sorting
 *
 * 2009/12/26: initial release by Todd Xue
 */

#ifndef _sort_h
#define _sort_h

inline bool is_sorted(int n, int* a) { for (int i = 0; i < n-1; ++i) { if (a[i] > a[i+1]) return false; } return true; }

void sort_1_to_n_inplace(int n, int* a);

/**
 * partition
 */
bool is_partitioned(int n, int* a, int pivot, int m);
int partition_brute_force(int n, int* a, int pivot);
int partition(int n, int* a, int pivot);

void sort_quick(int n, int* a);

#endif
