/*
 * sort.h --
 *
 * algorithms related to misc sorting
 *
 * 2009/12/26: initial release by Todd Xue
 */

#ifndef _sort_h
#define _sort_h

void sort_1_to_n_inplace(int n, int* a);

/**
 * partition
 */
bool is_partitioned(int n, int* a, int pivot, int m);
int partition_brute_force(int n, int* a, int pivot);
int partition(int n, int* a, int pivot);

#endif
