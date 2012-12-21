#include "shuffle.h"

namespace shuffle { namespace in_shuffle {

        /**
         * 1st one: devide and conqer suggested by Leo Zhu
         */
        void devide_and_conquer(int n, int* a) 
        {
            /**
             * terminate condition
             * n == 2
             */
            if (n <= 2)
                return;

            int m = n / 2;
            int l = m / 2;
            
            /**
             * devide by shift right the middle part
             *
             * [0,l) [l, m, m+l) [m+l, n)
             */
            shift_right(m, a+l, l);

            /**
             * conquer each sub part
             * [0, l) [l, 2l) [2l, n)
             */
            devide_and_conquer(2*l, a);
            devide_and_conquer(n-2*l, a+2*l);
        }

        /**
         * 2rd one: 2 is primitive root of prime P where P is very close to n
         */
        int primtive_root_2_primes[] = {
            /**
             * >grep '^[1-9]' t/shuffle/primitive-root-2.pl | perl -lane 'print $F[2] if $F[0] < 32' | xargs echo | perl -lane 'print join ",", @F'
             */
            3,5,13,29,61,107,227,509,1019,2029,4093,8179,16381,32749,65371,131059,262139,524269,1048573,
            2096789,4193789,8386949,16776989,33552749,67108109,134215349,268435109,536869637,1073740517,2147483477
        };
        
        void primitive_root_prime(int n, int* a) {
            int p = n - 1;
            
            /**
             * 1 cycles only:
             * 1 -> 2 -> 4 -> .... -> 2^^(p-1) = 1 MOD(p)
             * 
             * and 2 trivial case:
             *  0 -> 0
             *  p -> p
             * where we don't need any actions
             */
            int pos = 1;
            int pos_value = a[pos];
            for (int i = 1; i <= p-2; ++i) {

                int pos_next = n * 2 % p;
                int pos_next_value = a[pos_next];

                a[pos_next] = pos_value;
                pos = pos_next;
                pos_value = pos_next_value;
            }
        }


        int find_closest_prime(int n) {
            for (int i = sizeof(primtive_root_2_primes)/sizeof(int)-1; i>=0; --i) {
                if (n >= primtive_root_2_primes[i])
                    return primtive_root_2_primes[i];
            }
            return 0;
        }

        void primitive_root(int n, int* a)
        {
            /**
             * TERMINATE condition
             */
            if (n <= 2) return;

            int p = find_closest_prime(n);

            int l = (p+1)/2;
            int r = (n+1)/2 - l;
            
            /**
             * Before shift:
             * |---l---| |--r--| |---l---| |--r--|
             *           ^^^^^^^^^^^^^^^^^
             * 
             * After shift:
             * 
             * |---l---| |---l---| |--r--| |--r--|
             *           ^^^^^^^^^^^^^^^^^
             */
            shift_right(r+l, a+l, l);
            primitive_root_prime(p + 1, a);
            primitive_root(n - (p + 1), a);
        }

    }
}
