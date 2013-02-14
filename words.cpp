#include "words.h"

/**
 * split string into words
 * backtrack
 * 
 * currently it's non greedy, we can easily change it into greedy
 * by change the loop from end to begin
 */
bool split_words(char const* str, std::vector<word>& words)
{
    if (*str == '\0')
        return true;
    
    char const* b = str;
    char const* e = b;
    
    do {
        ++e;
        word w(b, e);
        
        /**
         * greedy if loop reversed
         */
        for (int i = 0; i < sizeof(dict)/sizeof(dict[0]); ++i) {
            if (w == dict[i]) {
                words.push_back(w);
                if (split_words(e, words))
                    return true;
                words.pop_back();
            }
        }
    } while (*e);

    return false;
}

/**
 * calculate the count of valid splits
 * in this case, DP words
 */
int split_words_ways(char const* str)
{
    int n = strlen(str);
    int* counts = new int[n+1];

    /**
     * counts[i] = sum { counts[j] and str[j..i) is a valid word
     *             j
     * 
     * counts[0] = 1; // tricky init value here :(
     */

    counts[0] = 1;
    for (int i = 1; i <=n; ++i) {
        counts[i] = 0;
        for (int j = 0; j < i; ++j) {
            word w(str+j, str+i);
            for (int k = 0; k < sizeof(dict)/sizeof(dict[0]); ++k) {
                if (w == dict[k]) {
                    counts[i] += counts[j];
                }
            }
        }
    }
    
    int count = counts[n];
    delete[] counts;
    return count;
}

