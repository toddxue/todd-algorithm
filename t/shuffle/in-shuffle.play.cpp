#include "shuffle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    bool use_primitive_root = false;
    int n = argc-1;
    if (0 == strcmp(argv[1], "p")) {
        --n;
        use_primitive_root = true;
    }

    if (n % 2 != 0) {
        fprintf(stderr, "expect even numbers of integers\n");
        return 1;
    }

    int* a = new int[n];

    for (int i = argc - n; i < argc; ++i)
        a[i-1] = strtol(argv[i], 0, 10);

    shuffle::in_shuffle::devide_and_conquer(n, a);
    for (int i = 0; i < n; ++i)
        fprintf(stdout, "%d ", a[i]);

    delete[] a;
    return 0;
}
