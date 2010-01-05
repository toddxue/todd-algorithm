#include "timed.h"
#include "max.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

    // the count only algorithm is really fast, it's the true O(nlog(n)) algorithm
    int na = strtol(argv[1], 0, 10);
    int bound = strtol(argv[2], 0, 10);
    {
        int* a = new int[na];
        for (int i = 0; i < na; ++i) {
            a[i] = random() % bound;
        }
        int nsub;
        {
            TIMED_BLOCK_STDERR(max_increase_sequence_count, true);
            nsub = max_increase_sequence_count(na, a);
        }
        printf("nsub = %d\n", nsub);
    }
    return 0;
}
