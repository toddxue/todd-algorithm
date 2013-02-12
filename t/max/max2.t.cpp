#include "TAP.h"
#include "max.h"
#include <limits.h>

int main(int argc, char* argv[]) {
    OK_SUM();

    int max, max2;

    {
        int a2[] = {1, 2};
        max2_fbt(2, a2, max, max2);
        OK(max == 2 && max2 == 1);
    }

    {
        int a2[] = {1, 2, 3};
        max2_fbt(sizeof(a2)/sizeof(a2[0]), a2, max, max2);
        OK(max == 3 && max2 == 2);
    }

    {
        int a2[] = {1, 2, 3, 4, 5, 6};
        max2_fbt(sizeof(a2)/sizeof(a2[0]), a2, max, max2);
        OK(max == 6 && max2 == 5);
    }

    {
        int a2[] = {1, 2, 6, 4, 5, 3};
        max2_fbt(sizeof(a2)/sizeof(a2[0]), a2, max, max2);
        OK(max == 6 && max2 == 5);
    }

    return 0;
}
