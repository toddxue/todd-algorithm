#include "TAP.h"
#include "sort.h"
#include <limits.h>
#include <algorithm>

bool verify_sort_1_to_n_inplace(int n) {
    int* a = new int[n];
    int* b = new int[n];
    for (int i = 0; i < n; ++i) a[i] = i;

    do {
        for (int i = 0; i < n; ++i) b[i] = a[i];
        sort_1_to_n_inplace(n, b);
        for (int i = 0; i < n; ++i) 
            if (b[i] != i) {
                fprintf(stderr, "sort failed for\n  ");
                for (int j = 0; j < n; ++j) 
                    fprintf(stderr, " %d", a[j]);
                fprintf(stderr, "\n-->\n  ");
                for (int j = 0; j < n; ++j) 
                    fprintf(stderr, " %d", b[j]);
                fprintf(stderr, "\n");
                return false;
            }
        
    } while (std::next_permutation(a, a+n));

    delete[] b;
    delete[] a;
    return true;
}

int main(int argc, char* argv[]) {
    OK_SUM();
    
    OK(verify_sort_1_to_n_inplace(1));
    OK(verify_sort_1_to_n_inplace(2));
    OK(verify_sort_1_to_n_inplace(3));
    OK(verify_sort_1_to_n_inplace(4));
    OK(verify_sort_1_to_n_inplace(5));
    OK(verify_sort_1_to_n_inplace(6));
    OK(verify_sort_1_to_n_inplace(7));
    OK(verify_sort_1_to_n_inplace(8));
    OK(verify_sort_1_to_n_inplace(9));

    return 0;
}
