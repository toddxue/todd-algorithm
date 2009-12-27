#include "TAP.h"
#include "max.h"
#include <limits.h>

int main(int argc, char* argv[]) {
    OK_SUM(*argv);

    OK(INT_MIN == max(0));
    OK(1 == max(1, 1));

    return 0;
}
