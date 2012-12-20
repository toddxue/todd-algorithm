#include "shuffle.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int n = argc-1;
    int* a = new int[n];

    for (int i = 1; i < argc; ++i)
        a[i-1] = strtol(argv[i], 0, 10);

    shuffle::in_shuffle::devide_and_conquer(n, a);
    for (int i = 0; i < n; ++i)
        fprintf(stdout, "%d ", a[i]);

    delete[] a;
    return 0;
}
