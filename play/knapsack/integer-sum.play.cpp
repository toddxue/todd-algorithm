#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "knapsack.h"

int main(int argc, char* argv[]) {

    if (argc < 2)
        return 0;

    int target_sum = strtol(argv[1], 0, 10);
    int n = argc - 2;
    int* a = new int[n];
    int* o = new int[n];
    for (int i = 2; i < argc; ++i)
        a[i-2] = strtol(argv[i], 0, 10);

    int o_c = knapsack::integer::find_sum(n, a, target_sum, o);

    for (int i = 0; i < o_c; ++i)
        printf("%d ", o[i]);
    printf("\n");

    return 0;
}

