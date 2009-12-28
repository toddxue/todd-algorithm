#include "TAP.h"
#include "max.h"
#include <limits.h>
#include <stdarg.h>

int max_partial_sum_circle_stupid(int n, int* a) {
    int max = INT_MIN;
    int sum;
    for (int i = 0; i < n; ++i) {
        sum = 0;
        for (int j = i; j < i+n; ++j) {
            sum += a[j % n];
            if (sum > max) max = sum;
        }
    }
    return max;
}

bool random_check(int n, int max, int c) {
    int* a = new int[n];
    
    bool ok = true;
    for (int cc = 0; cc < c; ++cc) {
        for (int i = 0; i < n; ++i) {
            a[i] = random() % max; 
            if (random() % 2) 
                a[i] = -a[i];
        }
        int sum1 = max_partial_sum_circle(n, a);
        int sum2 = max_partial_sum_circle_stupid(n, a);

        if (sum1 != sum2) {
            for (int i = 0; i < n; ++i) 
                printf("%d ", a[i]);
            printf("\nsum = %d, stupid=%d\n", sum1, sum2);
            ok = false;
            break;
        }
    }
    delete[] a;
    return ok;
}

static
int my_max_partial_sum_circle(int c, ...) {
    int* a = new int[c];
    va_list ap;
    va_start(ap, c);
    for (int i = 0; i < c; ++i)
        a[i] = va_arg(ap, int);
    int sum = max_partial_sum_circle(c, a);
    delete[] a;
    return sum;
}

int main(int argc, char* argv[]) {
    OK_SUM();

    OK(my_max_partial_sum_circle(3, 3, -1, 2) == 5);

    // 1 int
    OK(my_max_partial_sum_circle(1, 1) == 1);
    
    // 2 ints
    OK(my_max_partial_sum_circle(2, 1, 1) == 2);
    OK(my_max_partial_sum_circle(2, 1, -1) == 1);
    OK(my_max_partial_sum_circle(2, -1, 1) == 1);

    // 3 ints
    OK(my_max_partial_sum_circle(3, 1, 1, 1) == 3);

    OK(my_max_partial_sum_circle(3, 1, -1, -1) == 1);
    OK(my_max_partial_sum_circle(3, -1, 1, -1) == 1);
    OK(my_max_partial_sum_circle(3, -1, -1, 1) == 1);

    OK(my_max_partial_sum_circle(3, 2, -1, -1) == 2);
    OK(my_max_partial_sum_circle(3, -1, 2, -1) == 2);
    OK(my_max_partial_sum_circle(3, -1, -1, 2) == 2);

    // 4 ints
    OK(my_max_partial_sum_circle(4, 1, 1, -1, -1) == 2);
    OK(my_max_partial_sum_circle(4, 1, -1, 1, -1) == 1);
    OK(my_max_partial_sum_circle(4, 1, -1, -1, 1) == 2);

    OK(my_max_partial_sum_circle(4, -1, -1, 1, 1) == 2);
    OK(my_max_partial_sum_circle(4, -1, 1, -1, 1) == 1);
    OK(my_max_partial_sum_circle(4, -1, 1, 1, -1) == 2);

    // 5 ints
    OK(my_max_partial_sum_circle(5, 1, 1, -1, -1, 5) == 7);
    OK(my_max_partial_sum_circle(5, 1, -1, 1, -1, 2) == 3);
    OK(my_max_partial_sum_circle(5, 1, -1, -1, 1, 1) == 3);

    OK(my_max_partial_sum_circle(5, 1, -1, 1, -1, 1) == 2);

    // random tests, maybe slow, but not too slow to be used as testcases
    OK(random_check(1, 10, 1000));

    OK(random_check(2, 2, 1000));

    OK(random_check(4, 5, 80000));
    OK(random_check(4, 10, 40000));

    OK(random_check(4, 15, 20000));
    OK(random_check(4, 20, 10000));

    OK(random_check(20, 5, 10000));
    OK(random_check(20, 10, 10000));

    OK(random_check(30, 5, 10000));
    OK(random_check(30, 10, 10000));

    OK(random_check(40, 5, 10000));
    OK(random_check(40, 10, 10000));

    return 0;
}
