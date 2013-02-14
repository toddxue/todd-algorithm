/*
 * words.h --
 *
 * algorithms related to the calculation of the words
 *
 * Tue, Feb 12, 2013  3:57:22 PM: initial release by Todd Xue
 */

#ifndef _words_h
#define _words_h

#include "lists.h"

/**
 * some words operations
 */
struct word {
    char const* b;
    char const* e;

    word(char const* b, char const* e) : b(b), e(e) {}
    word(char const* str) : b(str), e(str) { while (*e) ++e; }
    int len() const { return e - b; }
    char operator [] (int i) const { return b[i]; }
};

inline bool operator == (word const& a, word const& b) {
    int l = a.len();
    if (l != b.len()) return false;
    for (int i = 0; i < l; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}
inline bool operator == (word const& a, char const* str) { word b(str); return a == b; }
inline bool operator == (char const* str, word const& a) { return a == str; }

/**
 * split string into words
 */
#include <vector>
bool split_words(char const* str, std::vector<word>& words, int dict_len, word const* dict); // backtrack
int  split_words_ways(char const* str, int dict_len, word const* dict); // only counting
int  split_words_shortest(char const* str, int dict_len, word const* dict); // 
int  split_minimum_words(char const* str, std::vector<word>& words, int dict_len, word const* dict);
int  split_maximum_words(char const* str, std::vector<word>& words, int dict_len, word const* dict);

#endif
