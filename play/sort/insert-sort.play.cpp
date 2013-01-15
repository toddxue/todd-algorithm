#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int n = argc-1;
    int* a = new int[n];
    for (int i = 0; i < n; ++i)
        a[i] = strtol(argv[i+1], 0, 10);

    int reverse_count = insert_sort(n, a);
    printf("%d\n", reverse_count);
    if (getenv("output")) {
        for (int i = 0; i < n; ++i)
            printf("%d ", a[i]);
        printf("\n");
    }
    
    delete[] a;
    return 0;
}
