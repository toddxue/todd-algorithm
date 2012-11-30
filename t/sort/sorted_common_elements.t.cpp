#include "TAP.h"
#include "sort.h"
#include "rpermut.h"

int main(int argc, char* argv[]) {
    OK_SUM();

    {
        int a1[] = {1, 2};
        int a2[] = {3, 4};
        int out[2];
        OK(0 == sorted_common_elements_brute_force(alen(a1), a1, alen(a2), a2, out));
    }

    {
        int a1[] = {};
        int a2[] = {3, 4};
        int out[2];
        OK(0 == sorted_common_elements_brute_force(0, a1, alen(a2), a2, out));
    }

    {
        int a1[] = {};
        int a2[] = {3};
        int out[2];
        OK(0 == sorted_common_elements_brute_force(0, a1, alen(a2), a2, out));
    }

    {
        int a1[] = {};
        int a2[] = {};
        int out[2];
        OK(0 == sorted_common_elements_brute_force(0, a1, 0, a2, out));
    }

    {
        int a1[] = {1, 2, 3};
        int a2[] = {3, 4};
        int out[2];
        OK(1 == sorted_common_elements_brute_force(alen(a1), a1, alen(a2), a2, out) && out[0] == 3);
    }

    {
        int a1[] = {1, 2};
        int a2[] = {3, 4};
        int out[2];
        OK(0 == sorted_common_elements(alen(a1), a1, alen(a2), a2, out));
    }

    {
        int a1[] = {};
        int a2[] = {3, 4};
        int out[2];
        OK(0 == sorted_common_elements(0, a1, alen(a2), a2, out));
    }

    {
        int a1[] = {};
        int a2[] = {3};
        int out[2];
        OK(0 == sorted_common_elements(0, a1, alen(a2), a2, out));
    }

    {
        int a1[] = {};
        int a2[] = {};
        int out[2];
        OK(0 == sorted_common_elements(0, a1, 0, a2, out));
    }

    {
        int a1[] = {1, 2, 3};
        int a2[] = {3, 4};
        int out[2];
        OK(1 == sorted_common_elements(alen(a1), a1, alen(a2), a2, out) && out[0] == 3);
    }

    return 0;
}
