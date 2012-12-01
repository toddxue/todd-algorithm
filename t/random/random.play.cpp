#include "random.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int opt_char;

    /**
     * long options is not portal using getopt, ignored.
     */
    while ((opt_char = getopt(argc, argv, "hs:")) != -1) {
        switch (opt_char) {
        case 's': 
            int seed = strtol(optarg, 0, 10); 
            srand(seed);
            break;

        case 'h': 
            fprintf(stderr, "Usage: %s -s<SEED> integer-list\n", argv[0]);
            exit(1);

        case '?':
            exit(1);
        }
    }

    int len = argc-optind;
    int* a = new int[len];
    for (int i = 0; i < len; ++i)
        a[i] = strtol(argv[optind+i], 0, 10);

    random_permutation(len, a);
    for (int i = 0; i < len; ++i)
        fprintf(stdout, "%d ", a[i]);
    fprintf(stdout, "\n");
    
    delete a;
    return 0;
}
