/*
 * knapsack.h --
 *
 * algorithms related to the calculation of the knapsack
 *
 * Fri Feb  1 10:25:32 PST 2013: initial release by Todd Xue
 */

#ifndef _knapsack_h
#define _knapsack_h

/**
 * some knapsack operations
 * mainly dynamic programming
 */

namespace knapsack {

    /**
     * input are integers
     */
    namespace integer {

        /**
         * C = find_sum(a[0..n), sum, out)
         * and
         * out[0] + ... + out[C-1] = sum
         *
         * if not available, C = 0
         *
         * NOTE: Simpler version to suppose all a[i] > 0
         */
        inline
        int find_sum(int n, int* a, int target_sum, int* out) {

            int max = 0;
            for (int i = 0; i < n; ++i) max += a[i];

            if (target_sum > max)
                return 0;

            if (target_sum == max) {
                for (int i = 0; i < n; ++i)
                    out[i] = a[i];
                return n;
            }
            
            //max = target_sum + 1; // to same some space
                
            /**
             * dynamic memory matrix:
             *   (sum, i)   --> (sum * n + i) = E
             *   (E/n, E%n) <-- E
             *
             * Simplified: 
             *   Matrix[E] == the prev last index of array to reach the sum
             *   Special case: 
             *       -2 means no solution
             *       -1 means (a[i] == sum) in current position
             */
            int* Matrix = new int[max * n];
            int out_c = 0;
            for (int i = 0; i < n; ++i) {

                /**
                 * now a[i] is the last element of the sum
                 */
                int sum = 0;
                for (; sum <= target_sum; ++sum) {
                    Matrix[sum * n + i] = -2;
                    int prev_sum = sum - a[i];

                    if (prev_sum == 0)
                        Matrix[sum * n + i] = -1;

                    else if(prev_sum > 0)
                        /**
                         * find if prev_sum exists in a[0..i)
                         */
                        for (int j = 0; j < i; ++j)
                            if (Matrix[prev_sum * n + j] >= -1)
                                Matrix[sum * n + i] = j;
                }

                if (Matrix[target_sum * n + i] >= -1) {
                    /**
                     * we got one solution here
                     */
                    out[out_c++] = a[i];

                    int curr = i;
                    int sum = target_sum;
                    int prev;
                    while ((prev = Matrix[sum * n + curr]) >= 0) {
                        out[out_c++] = a[prev];
                        curr = prev;
                        sum -= a[prev];
                    }
                    break;
                }
            }
            delete[] Matrix;
            return out_c;
        }
    }
}

#endif
