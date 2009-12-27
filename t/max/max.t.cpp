#include "TAP.h"
#include "max.h"
#include <limits.h>

int main(int argc, char* argv[]) {
    OK_SUM();

    OK(INT_MIN == max(0));
    OK(1 == max(1, 1));
    OK(3 == max(3, 1,2,3));
    OK(3 == max(3, 3,2,3));

    return 0;
}
