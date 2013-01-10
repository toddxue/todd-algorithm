#include "random.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <algorithm>

int main(int argc, char** argv)
{
    int opt_char;
    enum algorithm_t {
        e_null = 0,
        e_permutation = 1,
        e_subset = 2,
    };
    algorithm_t algorithm = e_null;

    /**
     * long options is not portal using getopt, ignored.
     */
    while ((opt_char = getopt(argc, argv, "hs:a:")) != -1) {
        switch (opt_char) {
        case 's': 
            {
            int seed = strtol(optarg, 0, 10); 
            srand(seed);
            break;
            }

        case 'a':
            switch (*optarg) {
            case 'p': 
                algorithm = e_permutation;
                break;
            case 's':
                algorithm = e_subset;
                break;
            default:
                fprintf(stderr, "unsupported algorithm %s\n", optarg);
                exit(1);
            }
            break;

        case 'h': 
            fprintf(stderr, "Usage: %s -s<SEED> integer-list\n", argv[0]);
            exit(1);

        case '?':
            exit(1);
        }
    }

    if (!algorithm) {
        fprintf(stderr, "algorithm(-a) not specified\n");
        exit(1);
    }

    switch(algorithm) {
    case e_permutation: 
        {
            int len = argc-optind;
            int* a = new int[len];
            for (int i = 0; i < len; ++i)
                a[i] = strtol(argv[optind+i], 0, 10);

            random_permutation(len, a);
            for (int i = 0; i < len; ++i)
                fprintf(stdout, "%d ", a[i]);
            fprintf(stdout, "\n");
            delete a;
            break;
        }
    case e_subset: 
        {
            int m = strtol(argv[optind], 0, 10);
            int len = argc-optind-1;
            int* b = new int[m];
            int* a = new int[len];
            for (int i = 0; i < len; ++i)
                a[i] = strtol(argv[optind+1+i], 0, 10);

            random_subset(len, a, m, b);
            std::sort(b, b+m);
            for (int i = 0; i < m; ++i)
                fprintf(stdout, "%d ", b[i]);
            fprintf(stdout, "\n");
            delete a;
            delete b;
            break;
        }
    }
    return 0;
}
