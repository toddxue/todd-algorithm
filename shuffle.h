/*
 * shuffle.h --
 *
 * algorithms related to shuffle
 *
 * Thu, Dec 20, 2012  2:22:38 PM: initial release by Todd Xue
 */

#ifndef _shuffle_h
#define _shuffle_h

namespace shuffle {

    inline void swap(int& a, int &b) { int tmp = a; a = b; b = tmp; }
    inline void reverse(int n, int* a) { for (int i = 0, j=n-1; i < j; ++i, --j) swap(a[i], a[j]); }

    /**
     * Basic one: shift right:
     *    a1, a2, ..., a_k, b_1, b_2, ..., b_m
     *    -->
     *    b_1, b_2, ..., b_m, a1, a2, ..., a_k
     * 
     * where n = k + m
     */
    inline void shift_right(int n, int* a, int m) {
        /**
         * this algorithm uses 3 reverse 
         */
        reverse(n, a);
        reverse(m, a);
        reverse(n-m, a+m);
    }

    /**
     * in-shuffle:
     * 
     *   a1, a2, ..., a_n, b_1, b_2, ..., b_n 
     *   -->
     *   a1, b1, a2, b2, ...,   ..., a_n, b_n
     */
    namespace in_shuffle {

        /**
         * overall
         * pre condition:  n is even below
         */
        
        /**
         * 1st one: devide and conqer suggested by Leo Zhu
         */
        void devide_and_conquer(int n, int* a);

        /**
         * 2rd one: 2 is primitive root of prime P where P is very close to n
         */
        void primitive_root(int n, int* a);

        /**
         * NOTE:
         * 
         * Performance:
         *   The 2nd one is linear algorithm which is far faster than the 1st one
         *   
         *   >t/shuffle/in-shuffle.play benchmark p {1..42346}  >/dev/null
         *   0.678ms/user
         *  
         *   >t/shuffle/in-shuffle.play benchmark {1..42346}  >/dev/null
         *   2.621ms/user
         *
         * As n doubled, it'll become 10 times faster, then 20, 40, ... until inplace shuffle becomes meanless 
         * since no memory can hold them all :)
         * 
         * About primitive_root
         *   There are lot of alternatives, e.g. 
         *   1. Choose n=3^K+1, there are K cycles
         *      "A Simple In-Place Algorithm for In-Shuffle"
         *      FROM Peiyush Jain, Microsoft Corporation. July 2004
         *   2. General Cycle heads study: 
         *      "Computing the Cycles in the Perfect Shuffle Permutation"
         *      FROM JOHN ELLIS, TOBIAS KRAHN, HONGBING FAN, May 2000
         * 
         *
         */
    }
}

#endif
