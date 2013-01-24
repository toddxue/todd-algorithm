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
    /**
     * max length sub string which is a palindrome
     * output goes into [pb, pe)
     */
    void max_substr_simple(int n, char const* s, char const*& pb, char const*& pe);
    void max_substr_center(int n, char const* s, char const*& pb, char const*& pe);
    void max_substr_Manacher(int n, char const* s, char const*& pb, char const*& pe, int* buffer);
}


#endif
