#include "TAP.h"
#include "max.h"
#include <limits.h>

bool rcheck(int na, int bound) {
    int* a = new int[na];
    int* sub1 = new int[na];
    int* sub2 = new int[na];

    for (int i = 0; i < na; ++i)
        a[i] = random() % bound;

    int max_increase_sequence1(int na, int* a, int* sub);
    int nsub1 = max_increase_sequence1(na, a, sub1);
    int nsub2 = max_increase_sequence (na, a, sub2);

    int r = nsub1 == nsub2;

    if (!r) {
        printf("sub1: ");
        for (int i = 0; i < nsub1; ++i)
            printf("%d ", sub1[i]);
        printf("\n");

        printf("sub2: ");
        for (int i = 0; i < nsub2; ++i)
            printf("%d ", sub2[i]);
        printf("\n");
    }

    return r;
}

int main(int argc, char* argv[]) {

    OK_SUM();

    {
        int a[] = {1, 2, -1, 0};
        int sub[4];
        int nsub = max_increase_sequence(4, a, sub);
        OK(2 == nsub);
    }

    {
        int a[] = {4, 3, 2, 1};
        int sub[4];
        int nsub = max_increase_sequence(4, a, sub);
        OK(1 == nsub);
    }

    {
        int a[] = {4, 1, 2, 3};
        int sub[4];
        int nsub = max_increase_sequence(4, a, sub);
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

