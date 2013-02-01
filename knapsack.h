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

            /**
             * to speed up the lookup of sum in a[0...i] so far
             */
            int* RightMostIndex = new int [max];
            for (int sum = 0; sum < max; ++sum)
                RightMostIndex[sum] = -1;
            
            int out_c = 0;
            for (int i = 0; i < n; ++i) {

                /**
                 * now a[i] is the last element of the sum
                 * the reverse order iteration of target_sum->0 is important
                 * or a[i] will be repeatly counted
                 */
                for (int sum = target_sum; sum >= 0; --sum) {
                    Matrix[sum * n + i] = -2;
                    int prev_sum = sum - a[i];

                    if (prev_sum == 0) {
                        Matrix[sum * n + i] = -1;
                        RightMostIndex[sum] = i;
                    }
                    else if(prev_sum > 0) {
                        /**
                         * find if prev_sum exists in a[0..i)
                         */
                        if (RightMostIndex[prev_sum] >= 0) {
                            Matrix[sum * n + i] = RightMostIndex[prev_sum];
                            RightMostIndex[sum] = i;
                        }
                    }
                }

                if (Matrix[target_sum * n + i] >= -1) {
                    /**
                     * we got one solution here,
                     * notorious to write down correctly this part of codes, 
                     * why :( :(
                     */
                    int curr = i;
                    int sum = target_sum;
                    int prev;
                    while ((prev = Matrix[sum * n + curr]) >= -1) {
                        out[out_c++] = a[curr];
                        sum -= a[curr];
                        curr = prev;

                        if (curr == -1) 
                            break;
                    }
                    break;
                }
            }
            delete[] Matrix;
            delete[] RightMostIndex;
            return out_c;
        }
    }
}

#endif
