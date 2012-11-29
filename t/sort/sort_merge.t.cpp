#include "TAP.h"
#include "sort.h"
#include "rpermut.h"

int vs[] = {-1, 0, 1, 2, 3, 4, 5, 6};
int a[10];

bool verify_sort_merge(int n) {

    for (int vs_len = 1; vs_len < 6; ++vs_len) {
        for (rpermut_begin(n, a, vs_len, vs); rpermut_next(n, a, vs_len, vs); ) {
            sort_merge(n, a);
            if (!is_sorted(n, a))
                return false;
        }
    }
    return true;
}



int main(int argc, char* argv[]) {
    OK_SUM();
    
    OK(verify_sort_merge(1));
    OK(verify_sort_merge(2));
    OK(verify_sort_merge(3));
    OK(verify_sort_merge(4));
    OK(verify_sort_merge(5));
    OK(verify_sort_merge(6));
    OK(verify_sort_merge(7));
    OK(verify_sort_merge(8));
    OK(verify_sort_merge(9));
    OK(verify_sort_merge(10));
    OK(verify_sort_merge(11));

    return 0;
}
