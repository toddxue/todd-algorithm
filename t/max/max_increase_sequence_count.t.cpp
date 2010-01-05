#include "TAP.h"
#include "max.h"
#include <limits.h>

bool rcheck(int na, int bound) {
    int* a = new int[na];
    int* sub1 = new int[na];

    for (int i = 0; i < na; ++i)
        a[i] = random() % bound;

    int max_increase_sequence1(int na, int* a, int* sub);
    int nsub1 = max_increase_sequence1(na, a, sub1);
    int nsub2 = max_increase_sequence_count (na, a);

    int r = nsub1 == nsub2;
    if (!r) {
        for (int i = 0; i < na; ++i)
            printf("%d ", a[i]);
        printf("\n nsub1 = %d, nsub2=%d\n", nsub1, nsub2);
    }
    delete[] sub1;
    return r;
}

int main(int argc, char* argv[]) {

    OK_SUM();

    {
        int a[] = {1, 2, -1, 0};
        int nsub = max_increase_sequence_count(4, a);
        OK(2 == nsub);
    }

    {
        int a[] = {4, 3, 2, 1};
        int nsub = max_increase_sequence_count(4, a);
        OK(1 == nsub);
    }

    {
        int a[] = {4, 1, 2, 3};
        int nsub = max_increase_sequence_count(4, a);
        OK(3 == nsub);
    }

    {
        int a[] = {1, 2, 1, 1};
        int nsub = max_increase_sequence_count(4, a);
        OK(3 == nsub);
    }


    // random test cases
    OK(rcheck(10, 3));
    OK(rcheck(10, 4));
    OK(rcheck(10, 5));
    OK(rcheck(10, 6));
    OK(rcheck(20, 3));
    OK(rcheck(20, 4));
    OK(rcheck(20, 5));
    OK(rcheck(20, 6));

    /*
    for (int i = 1; i < 20; ++i)
        for (int j = 1; j < 10; ++j)
            for (int c = 0; c < 10; ++c)
                OKx(rcheck(i, j));
    */
    return 0;
}

