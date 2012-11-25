#include "TAP.h"
#include "sort.h"
#include "rpermut.h"

int vs[] = {0, 1, 2, 3, 4, 5, 6};
int a[10];

bool verify_brute_force_partition(int n) {

    for (int pivot = -1; pivot < 8; ++pivot) {
        for (int vs_len = 1; vs_len < 6; ++vs_len) {
            for (rpermut_begin(n, a, vs_len, vs); rpermut_next(n, a, vs_len, vs); ) {
                int m = partition_brute_force(n, a, pivot);
                if (!is_partitioned(n, a, pivot, m))
                    return false;
            }
        }
    }
    return true;
}

bool verify_partition(int n) {

    for (int pivot = -1; pivot < 8; ++pivot) {
        for (int vs_len = 1; vs_len < 6; ++vs_len) {
            for (rpermut_begin(n, a, vs_len, vs); rpermut_next(n, a, vs_len, vs); ) {
                int m = partition(n, a, pivot);
                if (!is_partitioned(n, a, pivot, m))
                    return false;
            }
        }
    }
    return true;
}



int main(int argc, char* argv[]) {
    OK_SUM();
    
    OK(verify_brute_force_partition(1));
    OK(verify_brute_force_partition(2));
    OK(verify_brute_force_partition(3));
    OK(verify_brute_force_partition(4));
    OK(verify_brute_force_partition(5));
    OK(verify_brute_force_partition(6));
    OK(verify_brute_force_partition(7));
    OK(verify_brute_force_partition(8));
    
    OK(verify_partition(1));
    OK(verify_partition(2));
    OK(verify_partition(3));
    OK(verify_partition(4));
    OK(verify_partition(5));
    OK(verify_partition(6));
    OK(verify_partition(7));
    OK(verify_partition(8));

    return 0;
}
