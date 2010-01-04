#include "TAP.h"
#include "max.h"
#include <limits.h>

bool rcheck(int na, int nb, int bound) {
    int* a = new int[na];
    int* b = new int[nb];
    int nsub = na < nb ? na : nb;
    int* sub = new int[nsub];
    for (int i = 0; i < na; ++i)
        a[i] = random() % bound;
    for (int i = 0; i < nb; ++i)
        b[i] = random() % bound;

    int max_common_sub_sequence1(int na, int* a, int nb, int* b, int* sub);
    int nsub1 = max_common_sub_sequence1(na, a, nb, b, sub);
    int nsub2 = max_common_sub_sequence (na, a, nb, b, sub);

    return nsub1 == nsub2;
}

int main(int argc, char* argv[]) {
    OK_SUM();

    // 2 corner cases with na == 0
    OK(0 == max_common_sub_sequence(0, (int*)1, 0, (int*)1, (int*)0));
    OK(0 == max_common_sub_sequence(0, (int*)1, 1234, (int*)1234, (int*)0));

    // na == 1
    {
        int a[] = {1};
        int b[] = {1};
        int sub[1];
        OK(1 == max_common_sub_sequence(1, a, 1, b, sub) && sub[0] == 1);
    }

    {
        int a[] = {1};
        int b[] = {2};
        int sub[1];
        OK(0 == max_common_sub_sequence(1, a, 1, b, sub));
    }

    {
        int a[] = {1};
        int b[] = {2,1};
        int sub[1];
        OK(1 == max_common_sub_sequence(1, a, 2, b, sub) && sub[0] == 1);
    }

    // na == 2
    {
        int a[] = {1, 2};
        int b[] = {1, 2};
        int sub[2];
        OK(2 == max_common_sub_sequence(2, a, 2, b, sub) && sub[0] == 1  && sub[1] == 2);
    }

    {
        int a[] = {1, 2};
        int b[] = {0, 1, 2};
        int sub[2];
        OK(2 == max_common_sub_sequence(2, a, 3, b, sub) && sub[0] == 1  && sub[1] == 2);
    }

    {
        int a[] = {1, 2};
        int b[] = {3, 4};
        int sub[2];
        OK(0 == max_common_sub_sequence(2, a, 2, b, sub));
    }

    {
        int a[] = {1, 2};
        int b[] = {1, 3};
        int sub[2];
        OK(1 == max_common_sub_sequence(2, a, 2, b, sub) && sub[0] == 1);
    }

    {
        int a[] = {1, 2};
        int b[] = {2, 3};
        int sub[2];
        OK(1 == max_common_sub_sequence(2, a, 2, b, sub) && sub[0] == 2);
    }

    // misc cases
    {
        int a[] = {0, 1, 0, 2, 0, 3, 0};
        int b[] = {10, 1, 10, 2, 10, 3, 10};
        int sub[7];
        OK(3 == max_common_sub_sequence(7, a, 7, b, sub) && sub[0] == 1 && sub[1] == 2 && sub[2] == 3);
    }

    {
        int a[] = {0, 1, 0, 2, 0, 3, 0};
        int b[] = {10, 1, 10, 2, 10, 4, 10, 
                   10, 1, 10, 2, 10, 3, 10};
        int sub[7];
        OK(3 == max_common_sub_sequence(7, a, 14, b, sub) && sub[0] == 1 && sub[1] == 2 && sub[2] == 3);
        OK(3 == max_common_sub_sequence(14, b, 7, a, sub) && sub[0] == 1 && sub[1] == 2 && sub[2] == 3);
    }

    {
        int a[] = {0, 1, 0, 2, 0, 33, 0};
        int b[] = {10, 1, 10, 2, 10, 4, 10, 
                   10, 1, 10, 2, 10, 3, 10};
        int sub[7];
        OK(2 == max_common_sub_sequence(7, a, 14, b, sub) && sub[0] == 1 && sub[1] == 2);
        OK(2 == max_common_sub_sequence(14, b, 7, a, sub) && sub[0] == 1 && sub[1] == 2);
    }

    // random cases now
    OK(rcheck(10, 10, 2));
    OK(rcheck(10, 10, 3));
    OK(rcheck(10, 10, 4));
    OK(rcheck(10, 10, 5));
    OK(rcheck(20, 10, 2));
    OK(rcheck(20, 10, 3));
    OK(rcheck(20, 10, 4));
    OK(rcheck(20, 10, 5));

    /*
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 20; ++j)
            for (int bound = 1; bound < 5; ++bound)
                OKx(rcheck(i, j, bound));
    */

    return 0;
}
