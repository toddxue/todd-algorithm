#include <stdio.h>
#include <stdlib.h>
#include "max.h"

int main(int argc, char* argv[])
{
    int n = argc - 1;
    int* a = new int[n];

    for (int i = 1; i < argc; ++i)
        a[i-1] = strtol(argv[i], 0, 10);

    int dist = max_distance_less_than_brute_force(n, a);
    printf("%d", dist);

    int dist2 = max_distance_less_than_linear_time(n, a);
    printf("\t%d", dist2);

    delete[] a;
    return 0;
}

