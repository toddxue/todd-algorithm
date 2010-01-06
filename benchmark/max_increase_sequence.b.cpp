#include "timed.h"
#include "max.h"
#include <stdlib.h>

int max_increase_sequence1(int na, int* a, int* sub);

int main(int argc, char* argv[]) {

    // becomes very slow after na = 25 for version 1
    // same time for the 20000 for the 2nd version
    // (2*10^4) ** (n^3) => 8 * 10^12 = 80G, 
    // so it means n^3 is far from good when na is large

    // now it's a true time-O(nlog(n)) and space O(3n)
    // algorithm, when 10,000,000, it take about 2 secs
    // really fast and efficient! :)

    int na = strtol(argv[1], 0, 10);
    {
        int* a = new int[na];
        int* sub = new int[na];
        for (int i = 0; i < na; ++i) {
            a[i] = random() % 4;
        }
        TIMED_BLOCK_STDERR(max_increase_sequence, true);
        max_increase_sequence(na, a, sub);
    }
    return 0;
}
