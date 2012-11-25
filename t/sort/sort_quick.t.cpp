#include "TAP.h"
#include "sort.h"
#include "rpermut.h"

int vs[] = {-1, 0, 1, 2, 3, 4, 5, 6};
int a[10];

bool verify_sort_quick(int n) {

    for (int vs_len = 1; vs_len < 6; ++vs_len) {
        for (rpermut_begin(n, a, vs_len, vs); rpermut_next(n, a, vs_len, vs); ) {
            sort_quick(n, a);
            if (!is_sorted(n, a))
                return false;
        }
    }
    return true;
}



int main(int argc, char* argv[]) {
    OK_SUM();
    
    OK(verify_sort_quick(1));
    OK(verify_sort_quick(2));
    OK(verify_sort_quick(3));
    OK(verify_sort_quick(4));
    OK(verify_sort_quick(5));
    OK(verify_sort_quick(6));
    OK(verify_sort_quick(7));
    OK(verify_sort_quick(8));
    OK(verify_sort_quick(9));
    OK(verify_sort_quick(10));
    OK(verify_sort_quick(11));

    return 0;
}
