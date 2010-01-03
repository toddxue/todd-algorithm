#include "timed.h"
#include "max.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

    // c = 22 is already very slow for the 1st version: 4 seconds
    // after switch to version 2, now it becomes c = 200, we're 10 times faster
    // but still not enough fast
    int c = strtol(argv[1], 0, 10);
    {
        int a[1000];
        int b[1000];
        int sub[1000];
        for (int i = 0; i < c; ++i) {
            a[i] = random() % 3;
            b[i] = random() % 3;
        }
        TIMED_BLOCK_STDERR(max_common_sub_sequence, true);
        max_common_sub_sequence(c, a, c, b, sub);
    }
    return 0;
}
