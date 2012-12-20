#include "shuffle.h"

namespace shuffle { namespace in_suffle {

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
    }
}
