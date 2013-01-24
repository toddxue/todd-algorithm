#include "palindrome.h"

namespace palindrome {


    bool is_palindrome(char const* s, char const* s_end) 
    {
        for (; s < s_end; ++s, --s_end)
            if (*s != *s_end) 
                return false;
        return true;
    }


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
     */
    void max_substr_Manacher(int n, char const* s, char const*& pb, char const*& pe)
    {
        // pending...
    }
}
