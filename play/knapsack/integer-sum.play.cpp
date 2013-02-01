#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "knapsack.h"
#include "sort.h"

int main(int argc, char* argv[]) {

    if (argc < 2)
        return 1;

    int target_sum = strtol(argv[1], 0, 10);
    int n = argc - 2;
    int* a = new int[n];
    int* o = new int[n];
    for (int i = 2; i < argc; ++i)
        a[i-2] = strtol(argv[i], 0, 10);

    sort_quick(n, a);
    for (int i = 0, j = n-1; i < j; ++i, --j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    int o_c = knapsack::integer::find_sum(n, a, target_sum, o);

    int exit_status = 2;
    if (o_c > 0) {
        printf("%d = %d", target_sum, o[0]);
        for (int i = 1; i < o_c; ++i)
        printf(" + %d", o[i]);
        printf("\n");
        exit_status = 0;
    }

    delete[] o;
    delete[] a;
    return exit_status;
}

/**
 * 
 * At least correct now:
 * 
    >time ./integer-sum.play 50000 $(shuf -e {1..10}{1..10} {1..10}{1..10} {1..100} {1..100}{1..5})
    50000 = 903 + 910 + 91 + 494 + 1005 + 12 + 382 + 552 + 58 + 110 + 751 + 244 + 531 + 41 + 595 + 76 + 104 + 541 + 27 + 252 + 334 + 332 + 202 + 80 + 64 + 45 + 26 + 752 + 802 + 551 + 152 + 96 + 695 + 165 + 365 + 77 + 410 + 351 + 59 + 753 + 100 + 31 + 425 + 485 + 464 + 835 + 872 + 574 + 235 + 191 + 192 + 624 + 174 + 83 + 703 + 305 + 275 + 45 + 242 + 26 + 33 + 203 + 67 + 844 + 754 + 831 + 791 + 53 + 25 + 301 + 333 + 742 + 543 + 103 + 96 + 24 + 611 + 105 + 264 + 653 + 925 + 713 + 325 + 645 + 36 + 261 + 42 + 76 + 432 + 851 + 534 + 784 + 263 + 994 + 81 + 43 + 205 + 4 + 1001 + 555 + 68 + 993 + 403 + 193 + 183 + 161 + 233 + 625 + 684 + 78 + 21 + 794 + 57 + 612 + 153 + 121 + 95 + 992 + 92 + 982 + 88 + 864 + 632 + 715 + 401 + 635 + 212 + 971 + 885 + 40

    V1: O(max*n^2)
    real0m1.257s
    user0m1.197s
    sys0m0.059s

    V2: maintain sum with right most index array to reduce to O(max*n)
    real0m0.165s
    user0m0.102s
    sys0m0.062s

    V3: sort from biggest to smaller, reduce a little bit
    real0m0.124s
    user0m0.063s
    sys0m0.059s
 * 
 */

