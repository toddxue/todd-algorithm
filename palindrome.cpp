#include "palindrome.h"
#include "common.h"

namespace palindrome {


    /**
     * max length sub string which is a palindrome
     * output goes into out buffer, return the end position inside buffer
     */

    /**
     * Simple implementation, O(n^3):
     * 
     *   for [i,j] where 0 <= i <= j < n
     *   check whether s[i,j] is a palindrome
     */
    void max_substr_simple(int n, char const* s, char const*& pb, char const*& pe)
    {
        int max_i = 0, max_j = 0, max_len = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j)
                if (is_palindrome(s+i, s+j) && j-i+1 > max_len) 
                {
                    max_len = j-i + 1;
                    max_i = i;
                    max_j = j;
                }

        pb = s + max_i;
        pe = s + max_j + 1;
    }

    /**
     * Simple implementation, O(n^2):
     * 
     *   for each center, get the maximum palindrome
     *   then get max among these max
     *
     * Note:
     *   dynamic programming can achieve same O(n^2), 
     *   but ..hmm... need additional O(n^2) space ;)
     * 
     * Usually this one works almost linear, but jumps to n^2 quickly when most characters are same :(
     * then Manacher's algorithm really shines.
     */
    void max_substr_center(int n, char const* s, char const*& pb, char const*& pe)
    {
        pb = s; pe = s;
        char const* end = s + n;

        /**
         * center around a [cl, cr]
         * 
         * cl = cr:
         *   a b c b a
         *       ^
         *
         * cl + 1 = cr:
         *   a b b a
         *     ^ ^
         */
        char const *l, *r;
        for (char const* cl = s; cl != end; ++cl) {
            for (char const* cr = cl; cr != end && cr < cl+2; ++cr) {
                l = cl;
                r = cr;
                while (s < l && r+1 < end && l[-1] == r[+1])
                    --l, ++r;
                ++r;
                if (r - l > pe - pb) 
                    pb = l, pe = r;
            }
        }
    }

    /*
     * Manacher's algorithm O(n)
     * ^^^^^^^^^^^^^^^^^^^^
     * 
     * version only covers center on characters, not middle of them
     */
    void max_substr_Manacher(int n, char const* s, char const*& pb, char const*& pe, int* buffer)
    {
        char const* end = s + n-1;
        pb = pe = s;

        /**
         *  (big_center, big_radius, center, radius)
         * 
         *  a b c b a d a b c b a
         *            ^     ^
         *            |     | radius = 2
         *            |   center
         *            |
         *            | big_radius = 5
         *          big_center
         *
         * at each steps, we either move center or right, so at most took 2*n steps 
         */
        //int* radius = new int[n];
        //ARRMEM_GUARD(int, radius);
        int* radius = buffer;

        char const* big_center = s;
        int big_radius = 0;

        while (big_center + big_radius <= end) {

            /**
             * phase 1, build big center/radius
             */
            char const* l = big_center - big_radius;
            char const* r = big_center + big_radius;

            while (s < l && r < end && l[-1] == r[1])
                --l, ++r;

            if (r-l+1 > pe-pb) 
                pb = l, pe = r+1;

            big_radius = r - big_center;
            radius[big_center-s] = big_radius;

            /**
             * phase 2, move forward small center/radius
             * if center/radius moves out of [big_center-big_radius, big_center+big_radius]
             *   they becomes big_center/big_radius
             */
            char const* r_center = big_center+1;
            int r_radius = 0;
            for (; r_center < big_center + big_radius; ++r_center) {
                char const* l_center = big_center - (r_center - big_center);
                int l_radius = radius[l_center - s];
                if (l_center - l_radius <= big_center - big_radius) {
                    r_radius = big_center + big_radius - r_center;
                    break;
                }
                else
                    radius[r_center-s] = r_radius;
            }
            
            /**
             * now it's time to build next big_center
             */
            big_center = r_center;
            big_radius = r_radius;
        }
    }
}
