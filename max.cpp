/*
 * max.cpp --
 *
 * algorithms related to the calculation of the maximum
 *
 * 2009/12/26: initial release by Todd Xue
 */

#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "max.h"
#include "hash.h"

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
 *        after some concept proof, we got
 *          1. the max_partial_sum is greedy respected to range
 *          2. min == total means all hole-sum (=total-sum) <= 0
 *              a) all a[i] <= 0, no need to use hole-sum
 *              b) exist k such as a[k] > 0, max >= a[k] > max(hole-sum)
 *          3. min != total, max(hole-sum) = max(total-sum) = total-min
 *              in this case, choose MAX(total-min, max)
 *
 *      Finally, we need to calculate all these in 1 pass of the array, this
 *      need us writing a different loop compared against the non-circle one
 *
 *-------------------------------------------------------------------------
 */
int max_partial_sum_circle(int n, int* a) {

    int a0 = a[0];
    int max = a0;
    int min = a0;

    int single_max = a0;
    int single_min = a0;

    int total = 0;
    int sum_max = 0;
    int sum_min = 0;

    for (int i = 0; i < n; ++i) {

        int v = a[i];
        total += v;
        sum_max += v;
        sum_min += v;

        if (sum_max < 0) sum_max = 0;
        if (sum_max > max) max = sum_max;

        if (sum_min > 0) sum_min = 0;
        if (sum_min < min) min = sum_min;

        if (single_max < v) single_max = v;
        if (single_min > v) single_min = v;
    }

    if (single_max < 0) max = single_max;
    if (single_min > 0) min = single_min;

    if (min != total && total-min > max)
        max = total-min;

    return max;
}

/*
 *-------------------------------------------------------------------------
 *
 * max_common_sub_sequence --
 *      return a sequence which is sub sequence of both [a, a+na) and [b, b+nb)
 *      the result are stored into sub, the
 *      number of elements filled are returned to caller
 *
 *
 * PRE CONDTION:
 *      To make things simpler, all array suposed to <= 1024 elements
 *
 * RETURN:
 *      length of sub sequence
 *
 * NOTE:
 *      the 1st version is too simple to have bugs :), but it's too slow.
 *      it's an about O(na^na * nb ^nb).
 *
 *      the 2nd version will a little more complicated, the idea is to cache
 *      some already calculated result, so no need to recalculte
 *        Define result(i,j) = max_common_sub_sequence(na-i, a+i, nb-j, b+j)
 *        and flag it only is enough.
 *
 *
 *-------------------------------------------------------------------------
 */
int max_common_sub_sequence1(int na, int* a, int nb, int* b, int* sub) {

    int nsub = 0;
    for (int i = 0; i < na; ++i) {
        for (int j = 0; j < nb; ++j) {
            if (a[i] == b[j]) {
                int sub_tmp[1024] = {a[i]};
                int nsub_tmp = 1 + max_common_sub_sequence(na-i-1, a+i+1, nb-j-1, b+j+1, sub_tmp+1);
                if (nsub_tmp > nsub) {
                    nsub = nsub_tmp;
                    for (int k = 0; k < nsub; ++k) sub[k] = sub_tmp[k];
                }
            }
        }
    }
    return nsub;
}

struct MaxSeq {
    int hn;
    int hval;
    MaxSeq* hnext;
    int sub_c; 
    int* sub; 
};

int _max_common_sub_sequence2(int na, int* a, int nb, int* b, int** psub, int buckets_c, MaxSeq** buckets) {

    if (na == 0 || nb == 0)
        return 0;
    
    using namespace hash_chaining;

    int hn = (na << 16) | nb;
    int hval = hash_hval(hn);
    MaxSeq* max_seq = search_n(buckets_c, buckets, hval, hn);
    if (max_seq) {
        *psub = max_seq->sub;
        return max_seq->sub_c;
    }

    int nsub = 0;
    int sub[1024];
    for (int i = 0; i < na; ++i) {
        for (int j = 0; j < nb; ++j) {
            if (a[i] == b[j]) {
                int* psub_tmp;
                int nsub_tmp = 
                    _max_common_sub_sequence2(na-i-1, a+i+1, nb-j-1, b+j+1, &psub_tmp, buckets_c, buckets);
                if (nsub_tmp+1 > nsub) {
                    nsub = nsub_tmp+1;
                    sub[0] = a[i];
                    memcpy(sub+1, psub_tmp, nsub_tmp * sizeof(int));
                }
            }
        }
    }
    
    max_seq = new MaxSeq;
    max_seq->hn = hn;
    max_seq->hval = hval;
    max_seq->sub_c = nsub;
    max_seq->sub = new int[nsub];
    memcpy(max_seq->sub, sub, nsub * sizeof(int));
    insert(buckets_c, buckets, max_seq);

    *psub = max_seq->sub;
    return nsub;
}

int max_common_sub_sequence2(int na, int* a, int nb, int* b, int* sub) {

    int buckets_c = 0;
    for (int i = 0; i < na; ++i)
        for (int j = 0; j < nb; ++j)
            if (a[i] == b[j])
                ++buckets_c;
    
    if (buckets_c == 0)
        return 0;

    MaxSeq** buckets = new MaxSeq*[buckets_c];
    memset(buckets, 0, sizeof(MaxSeq*) * buckets_c);
    int* psub;
    int nsub = _max_common_sub_sequence2(na, a, nb, b, &psub, buckets_c, buckets);
    memcpy(sub, psub, nsub * sizeof(int));

    for (int i = 0; i < buckets_c; ++i) {
        MaxSeq* seq = buckets[i];
        while (seq) {
            MaxSeq* seq2 = seq;
            delete[] seq2->sub;
            delete seq2;
            seq = seq->hnext;
        }
    }
    delete[] buckets;
    return nsub;
}

int max_common_sub_sequence(int na, int* a, int nb, int* b, int* sub) {

    if (na == 0 || nb == 0)
        return 0;

    enum Orient { OWN = 0, LEFT = 1, DOWN = 2};
    int* table = new int[na*nb];

    int a0 = a[0];
    int b0 = b[0];

    table[0] = (a0 == b0) ? 1 : 0;

    for (int i = 1; i < na; ++i) {
        if (a[i] == b0)
            table[i] = 1;
        else
            table[i] = (table[i-1] & 0xFFFF) + (LEFT << 16);
    }

    for (int j = 1; j < nb; ++j) {
        if (a0 == b[j])
            table[na * j] = 1;
        else
            table[na * j] = (table[na * (j-1)] & 0xFFFF) + (DOWN << 16);
    }


    for (int j = 1; j < nb; ++j) {
        for (int i = 1; i < na; ++i) {
            if (a[i] == b[j]) {
                table[i + j * na] = 1 + (table[(i-1) + (j-1) * na] & 0xFFFF);
            }
            else {
                int left = table[(i-1) + j * na] & 0xFFFF;
                int down = table[i + (j-1) * na] & 0xFFFF;
                if (left > down)
                    table[i + j * na] = left + (LEFT << 16);
                else
                    table[i + j * na] = down + (DOWN << 16);
            }
        }
    }

    // finally output the overall
    int nsub = table[na-1 + (nb-1)*na] & 0xFFFF;
    int current_fill = nsub;

    int i = na-1;
    int j = nb-1;

    while (i >= 0 && j >= 0) {
        Orient ori = Orient(table[i + j * na] >> 16);
        int seq_len = table[i + j * na] & 0xFFFF;
        if (seq_len == 0)
            break;
        if (ori == LEFT) --i;
        else if (ori == DOWN) --j;
        else {
            sub[--current_fill] = a[i];
            --i, --j;
        }
    }
    delete[] table;
    if (current_fill != 0) {
        printf("something wrong!\n");
        return 0;
    }
    return nsub;
}


/*
 *-------------------------------------------------------------------------
 *
 * max_increase_sequence --
 *      the max of all sub sequence with
 *           sub[0] <= sub[1] <= ....
 *
 * RETURN:
 *      the length of such max sub sequence
 *
 * After thoughts:
 *      1. version 1 is very stupid, but hard to have bug
 *      2. version 2 using recursive, dont go further, took about O(N^3)
 *      3. final one is really elegant, the link list data structure **shines**
 *
 *-------------------------------------------------------------------------
 */
int max_increase_sequence1(int na, int* a, int* sub) {
    // 1st enumerate all subsets
    int* mark = new int[na];
    memset(mark, 0, sizeof(int) * na);

    int max = 0;

    int total = 1 << na; // 2^na, e.g. n==2, 1<<2 == 4 == 2^2
    for (int i = 1; i < total; ++i) {
        // add 1 operation
        int j = 0;
        while (mark[j] == 1) {
            mark[j] = 0;
            ++j;
        }
        mark[j] = 1;

        // decide if it's a increasement sequence
        bool is_increase = true;
        int prev = INT_MIN;
        int n = 0;
        for (int k = 0; k < na; ++k) {
            if (mark[k] == 1) {
                ++n;
                if (a[k] < prev) {
                    is_increase = false;
                    break;
                }
                prev = a[k];
            }
        }
        if (is_increase) {
            if (n > max) {
                max = n;
                int fill = 0;
                for (int k = 0; k < na; ++k) {
                    if (mark[k] == 1)
                        sub[fill++] = a[k];
                }
            }
        }
    }
    delete[] mark;
    return max;
}

/**
   a data diagram of a sample data demonstrates everything
   about this algorithm. Pending a math proof for this.
   this is a O(n^3) algorithm, compared to the above O(2^n)
   is there a O(n^2)?

   the interesting Q is:
     math proof vs test cases, which win? :)

   ---data diagram:----
      1 1 1 0 1 2 1 1 0 0 1:

      --> 1 1 0 1 2 1 1 0 0 1
      - 1

      --> 1 0 1 2 1 1 0 0 1
      - 1
      - 1 1

      --> 0 1 2 1 1 0 0 1
      - 0
      - 1 1

      --> 1 2 1 1 0 0 1
      - 0
      - 1 1
      - 1 1 1

      --> 2 1 1 0 0 1
      - 0
      - 1 1
      - 1 1 1
      - 1 1 1 2

      --> 1 1 0 0 1
      - 0
      - 1 1
      - 1 1 1
      - 1 1 1 1

      --> 1 0 0 1
      - 0
      - 1 1
      - 1 1 1
      - 1 1 1 1
      - 1 1 1 1 1

      --> 0 0 1
      - 0
      - 0 0
      - 1 1 1
      - 1 1 1 1
      - 1 1 1 1 1

      --> 0 1
      - 0
      - 0 0
      - 0 0 0
      - 1 1 1 1
      - 1 1 1 1 1

      --> 1
      - 0
      - 0 0
      - 0 0 0
      - 1 1 1 1
      - 1 1 1 1 1
      - 1 1 1 1 1 1

 */
int max_increase_sequence2(int na, int* a, int* sub) {
    int* seqs = new int[na*na];
    int last = 0;
    seqs[last*na + 0] = a[0];

#if defined(DEBUG_max_increase_sequence)
    printf("\n-->");
    for (int i = 0; i < na; ++i)
        printf(" %d", a[i]);
    printf("\n");
    printf("- %d\n", seqs[0]);
#endif

    for (int i = 1; i < na; ++i) {

#if defined(DEBUG_max_increase_sequence)
        printf("\n-->");
        for (int j = i; j < na; ++j)
            printf(" %d", a[j]);
        printf("\n");
#endif

        int v = a[i];

        int curr = last; {
            int curr_last = curr*na + curr;
            // promote to curr+1
            if (seqs[curr_last] <= v) {
                memcpy(&seqs[(curr+1)*na], &seqs[curr*na], (curr+1)*sizeof(int));
                seqs[(curr+1)*na + (curr+1)] = v;
                ++last;
            }
            // operation 2: replace the last element
            if (seqs[curr_last] > v && (curr == 0 || seqs[curr_last-1] <= v))
                seqs[curr_last] = v;
        }

        for (--curr; curr >= 0; --curr) {
            int curr_last = curr*na + curr;

            // operation 1: promote to curr+1
            if (seqs[curr_last] <= v && v < seqs[(curr+1)*na + (curr+1)]) {
                memcpy(&seqs[(curr+1)*na], &seqs[curr*na], (curr+1)*sizeof(int));
                seqs[(curr+1)*na + (curr+1)] = v;
            }

            // a trick to reduce some operations
            if (seqs[curr_last] <= v)
                break;

            // operation 2: replace the last element
            if (seqs[curr_last] > v && (curr == 0 || seqs[curr_last-1] <= v))
                seqs[curr_last] = v;
        }

#if defined(DEBUG_max_increase_sequence)
        for (int c = 0; c <= last; ++c) {
            printf("-");
            for (int j = 0; j <= c; ++j)
                printf(" %d", seqs[c*na + j]);
            printf("\n");
        }
#endif
    }
    for (int j = 0; j <= last; ++j)
        sub[j] = seqs[last*na + j];
    delete[] seqs;
    return last+1;
}

/**
   Note: there is a O(nlog(n)) algorithm, log(n)
   comes from the binary_search against the 
      smallest tail sub sequences below
   Also space O(n^2) can also be get rid of due to 
   we only need the tail element actually

   but such way, we only know the count
 */
int max_increase_sequence_count(int na, int* a) {
    int* min_tail = new int[na];
    min_tail[0] = a[0];
    int min_tail_c = 1;

    for (int i = 1; i < na; ++i) {
        int v = a[i];

        // one said binary search is never easy, it's true in this case
        // binary search to get the smallest pos which min_tail[pos] > v
        // the key point is not to find maxest pos which [pos] <= v
        int l = 0, r = min_tail_c-1;
        int m;
        while (l < r) {
            m = (l+r)/2;
            if (min_tail[m] <= v) 
                l = m+1;
            else 
                r = m;
        }
        int pos = l;
        if (min_tail[pos] <= v) // all <= v
            min_tail[min_tail_c++] = v;
        else if (pos == 0) // v < all
            min_tail[0] = v;
        else // [pos-1] <= v < [pos]
            min_tail[pos] = v;
    }
    delete[] min_tail;
    return min_tail_c;
}

int max_increase_sequence(int na, int* a, int* sub) {
    struct Node {
        int n;
        Node* prev;
    };
    Node* free_nodes = new Node[na];
    int free_nodes_curr = 0;

    Node** min_tail = new Node*[na];
    min_tail[0] = &free_nodes[free_nodes_curr++];
    min_tail[0]->n = a[0];
    min_tail[0]->prev = 0;
    int min_tail_c = 1;

    for (int i = 1; i < na; ++i) {
        int v = a[i];

        // one said binary search is never easy, it's true in this case
        // binary search to get the smallest pos which min_tail[pos] > v
        // the key point is not to find maxest pos which [pos] <= v
        int l = 0, r = min_tail_c-1;
        int m;
        while (l < r) {
            m = (l+r)/2;
            if (min_tail[m]->n <= v)
                l = m+1;
            else
                r = m;
        }
        int pos = l;
        if (min_tail[pos]->n <= v) { // all <= v
            min_tail[min_tail_c] = &free_nodes[free_nodes_curr++];
            min_tail[min_tail_c]->n = v;
            min_tail[min_tail_c]->prev = min_tail[min_tail_c-1];
            min_tail_c++;
        }
        else if (pos == 0) { // v < all
            min_tail[0] = &free_nodes[free_nodes_curr++];
            min_tail[0]->n = v;
            min_tail[0]->prev = 0;
        }
        else { // [pos-1] <= v < [pos]
            min_tail[pos] = &free_nodes[free_nodes_curr++];
            min_tail[pos]->n = v;
            min_tail[pos]->prev = min_tail[pos-1];
        }
    }
    int pos = min_tail_c;
    for (Node* node = min_tail[min_tail_c-1]; node; node = node->prev)
        sub[--pos] = node->n;

    delete[] min_tail;
    delete[] free_nodes;
    return min_tail_c;
}

