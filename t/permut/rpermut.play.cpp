#include "rpermut.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <count> <value-set-list>\n", argv[0]);
        exit(1);
    }

    size_t n = strtol(argv[1], 0, 10);
    size_t m = argc-2;

    int* vs = new int[m];
    int* a = new int[n];

    for (int i = 0; i < m; ++i)
        vs[i] = strtol(argv[i+2], 0, 10);

    if (rpermut_begin(n, a, m, vs)) {
        for (int i = 0; i < n; ++i) printf("%d\t", a[i]);
        printf("\n");

        while (rpermut_next(n, a, m, vs)) {
            for (int i = 0; i < n; ++i) printf("%d\t", a[i]);
            printf("\n");
        }
    }

    delete[] vs;
    delete[] a;
}

