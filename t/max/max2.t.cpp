#include "TAP.h"
#include "max.h"
#include <limits.h>

int main(int argc, char* argv[]) {
    OK_SUM();

    int max, max2;
    {
        int a2[] = {1, 2};
        max2_fbt(2, a2, max, max2);
        OK(max == 1 && max2 == 2);
    }

    return 0;
}
