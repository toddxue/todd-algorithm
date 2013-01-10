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

/**
 * partition 
 *    partition array into 2 sub array to support devide/conquer method
 *
 * logic:
 *    m = partition(n, a) so that
 *    a[0,m) <= pivot < a[m, n)
 */
bool is_partitioned(int n, int* a, int pivot, int m)
{
    for (int i = 0; i < m; ++i)
        if (a[i] > pivot)
            return false;

    for (int i = m; i < n; ++i)
        if (a[i] <= pivot)
            return false;

    return true;
}

/**
 * implementation 1: BRUTE-FORCE
 * but also have a advantage:
 *    keep original order of pairs if both <= pivot or both > pivot 
 *
 * single internal buffer also possible:
 * create single buffer,
 *   smaller array count from 0 to upwards,
 *   greater array count form n-1 to downwards
 */
int partition_brute_force(int n, int* a, int pivot)
{
    int* smaller = new int[n];
    int* greater = new int[n];

    int smaller_c = 0;
    int greater_c = 0;
    int m;

    for (int i = 0; i < n; ++i) {
        if (a[i] <= pivot)
            smaller[smaller_c++] = a[i];
        else
            greater[greater_c++] = a[i];
    }

    int i = 0;
    for (int smaller_i = 0; smaller_i < smaller_c; ++smaller_i) {
        a[i++] = smaller[smaller_i];
    }

    for (int greater_i = 0; greater_i < greater_c; ++greater_i) {
        a[i++] = greater[greater_i];
    }

    m = smaller_c;
    delete[] smaller;
    delete[] greater;
    return m;
}

/**
 * implementation 2: usual quick sort partition way
 * NOTE: there is SWAP, so order is not kept any more in partitions
 */
int partition(int n, int* a, int pivot)
{
    /**
     * initial state:
     * a[0,0) <= pivot < a[n, n)
     */
    int left = 0;
    int right = n;

    while (left < right) {

        if (a[left] <= pivot) {
            ++left;
            continue;
        }
        
        if (pivot < a[right-1]) {
            --right;
            continue;
        }

        /**
         * now a[left] > pivot >= a[right-1]
         * do a SWAP
         */
        if (left < right-1) {
            int tmp = a[left];
            a[left] = a[right-1];
            a[right-1] = tmp;

            /**
             * since left+1 < right
             * so below operation will not cause right < left
             */
            ++left;
            --right;
            continue;
        }
    }
    
    /**
     * now m == left == right
     * we have a[0,m) <= pivot < a[m, n)
     */
    return left;
}

void sort_quick(int n, int* a)
{
    if (n <= 1) return;

    int pivot = a[n-1];
    int m = partition(n, a, pivot);

    /**
     * now a[0,m) <= pivot < a[m, n)
     */

    /**
     * special case all <= pivot
     */
    if (m == n) {
        sort_quick(n-1, a);
        return;
    }

    /**
     * m can't be 0 now since a[0,m) at least contain pivot, must be 0<m<n
     */
    sort_quick(m, a);
    sort_quick(n-m, a+m);
}

/**
 * merge sort
 * buffer is the tricky part
 */
void sorted_merge(int n1, int* a1, int n2, int* a2, int* output)
{
    int output_i = 0;
    int i1 = 0;
    int i2 = 0;

    while (i1 < n1 && i2 < n2) {
        if (a1[i1] <= a2[i2])
            output[output_i++] = a1[i1++];
        else
            output[output_i++] = a2[i2++];
    }

    if (i1 == n1) {
        while (i2 < n2)
            output[output_i++] = a2[i2++];
    }
    else {
        while (i1 < n1)
            output[output_i++] = a1[i1++];
    }
}

void sort_merge_(int n, int* a, int* buffer)
{
    if (n <= 1)
        return;

    // [0, n) --> [0, middle) + [middle, n)
    int middle = n/2;
    sort_merge_(middle, a, buffer);
    sort_merge_(n-middle, a+middle, buffer);

    sorted_merge(middle, a, n-middle, a+middle, buffer);
    for (int i = 0; i < n; ++i)
        a[i] = buffer[i];
}

void sort_merge(int n, int* a)
{
    int* buffer = new int[n];
    sort_merge_(n, a, buffer);
    delete[] buffer;
}


/**
 * 
 * a related to problem to find common element of 2 sorted array
 * return value: the number of common elements which is stored inside out
 *
 * using merge logic
 */
int sorted_common_elements(int n1, int* a1, int n2, int* a2, int* out)
{
    int i1 = 0;
    int i2 = 0;
    int o_i = 0;
    while (i1 < n1 && i2 < n2) {
        int e1 = a1[i1];
        int e2 = a2[i2];
        if (e1 < e2)
            ++i1;
        else if (e2 < e1)
            ++i2;
        else {
            out[o_i++] = e1;
            ++i1;
            ++i2;
            while (i1 < n1 && a1[i1] == e1) ++i1;
            while (i2 < n2 && a2[i2] == e1) ++i2;
        }
    }
    return o_i;
}

/**
 * a simple one
 */
int sorted_common_elements_brute_force(int n1, int* a1, int n2, int* a2, int* out)
{
    int o_i = 0;
    for (int i1 = 0; i1 < n1; ++i1) {
        int e1 = a1[i1];
        for (int i2 = 0; i2 < n2; ++i2) {
            int e2 = a2[i2];
            if (e1 == e2) {
                if (o_i == 0)
                    out[o_i++] = e1;
                else if (out[o_i-1] != e1)
                    out[o_i++] = e1;
            }
        }
    }
    return o_i;
}

/**
 * insert sort to calculate the reverse number
 */
int insert_sort(int n, int* a)
{
    int reverse_count = 0;
    for (int j = 1; j < n; ++j) {
        int i = j-1;
        int a_j = a[j];
        if (a[i] > a_j) {
            do {
                a[i+1] = a[i];
                ++reverse_count;
                --i;
            } 
            while (i >= 0 && a[i] >= a_j);
            a[i+1] = a_j;
        }
    }
    return reverse_count;
}
