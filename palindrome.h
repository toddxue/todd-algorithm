/*
 * palindrome.h --
 *
 * algorithms related to the calculation of the palindromeimum 
 *
 * Wed, Jan 23, 2013  2:15:58 PM: initial release by Todd Xue
 */

#ifndef _palindrome_h
#define _palindrome_h

namespace palindrome {

    inline bool is_palindrome(char const* s, char const* s_end) {
        for (; s < s_end; ++s, --s_end)
            if (*s != *s_end) 
                return false;
        return true;
    }


    /**
     * max length sub string which is a palindrome
     * output goes into [pb, pe)
     */
    void max_substr_simple(int n, char const* s, char const*& pb, char const*& pe);
    void max_substr_center(int n, char const* s, char const*& pb, char const*& pe);
    void max_substr_Manacher(int n, char const* s, char const*& pb, char const*& pe, int* buffer);

    
    /**
     *  integer related palindrome
     */
    namespace integer {

        typedef unsigned int uint;
        
        inline char* get_digits(uint n, char* digits) {
            if (n == 0) {
                *digits++ = 0; 
                return digits;
            }

            while (n > 0) {
                *digits++ = n % 10;
                n /= 10;
            }
            return digits;
        }
        inline int get_number(char const* digits, char const* end) {
            int n = 0;
            for (--end; end >= digits; --end) {
                n *= 10;
                n += *end;
            }
            return n;
        }
        
        /**
         * - determine if is palindrom
         */
        inline bool is_palindrome(uint n) {
            if (n < 0) 
                return false;

            char digits[20];
            char* end = get_digits(n, digits);
            return palindrome::is_palindrome(digits, end - 1);
        }

        /**
         * - given an uinteger, find the closest number that is palindrome
         * 
         * hash table looks up doesn't work in this case, based on reflection rule compose, 
         * there are huge number of uintegers which are palindrome
         * 
         * but got some hints first:
         * 
         * 123 --> 121, closest, always adjust the last digits
         * 13  --> 11 
         * 
         * so seems pretty obvious to get this actually :)
         */
        inline uint closest_palindrome(uint n) {
            char digits[20];
            char* end = get_digits(n, digits);
            for (char *b = digits, *e = end-1; b < e; ++b, --e) {
                *b = *e;
            }
            return get_number(digits, end);
        }
    }
}


#endif
