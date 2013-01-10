#include "game24.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s n1 n2 n3 n4\n", argv[0]);
        return 1;
    }

    int a = strtol(argv[1], 0, 10);
    int b = strtol(argv[2], 0, 10);
    int c = strtol(argv[3], 0, 10);
    int d = strtol(argv[4], 0, 10);

    if (game24::exprs_for_24(a, b, c, d)) {
        return 0;
    }

    fprintf(stderr, "No solution\n");
    return 2;
}
