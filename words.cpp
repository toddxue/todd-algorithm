#include "words.h"

/**
 * split string into words
 * backtrack
 * 
 * currently it's non greedy, we can easily change it into greedy
 * by change the loop from end to begin
 */
bool split_words(char const* str, std::vector<word>& words, int dict_len, word const* dict)
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
        for (int i = 0; i < dict_len; ++i) {
            if (w == dict[i]) {
                words.push_back(w);
                if (split_words(e, words, dict_len, dict))
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
int split_words_ways(char const* str, int dict_len, word const* dict)
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
            for (int k = 0; k < dict_len; ++k) {
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

/**
 * split into minimum words, essentially same as shortest path, but this contexts are simpler
 */
int split_minimum_words(char const* str, std::vector<word>& words, int dict_len, word const* dict)
{
    int n = strlen(str);
    int* min_count = new int[n+1];
    int* min_split = new int[n+1];

    /**
     * 
     * min_count[i] = 1 + min { min_count[j] and str[j..i) is a valid word }
     *             j
     *
     * min_count[0] = 0
     *
     * we still have the choice of greedy or not if there are mulitple minimum values
     */

    min_count[0] = 0;
    min_split[0] = 0;
    
    for (int i = 1; i <=n; ++i) {
        min_count[i] = -1;
        min_split[i] = -1;
        
        int count = n+1;
        int split;
        for (int j = 0; j < i; ++j) {
            word w(str+j, str+i);
            for (int k = 0; k < dict_len; ++k) {
                if (w == dict[k] && min_count[j] >= 0) {
                    if (min_count[j]+1 < count) {
                        count = min_count[j]+1;
                        split = j;
                    }
                }
            }
        }
        if (count <= n) {
            min_count[i] = count;
            min_split[i] = split;
        }
    }
   
    int count = min_count[n];

    /**
     * output the minimum options now
     */
    {
        int b;
        int e = n;
        while (min_split[e] >= 0) {
            b = min_split[e];
            word w(str+b, str+e);
            words.push_back(w);
            
            e = b;
            if (e == 0)
                break;
        }
    }

    delete[] min_count;
    delete[] min_split;
    return count;
}


/**
 * split into maximum words, essentially same as shortest path, but this contexts are simpler
 */
int split_maximum_words(char const* str, std::vector<word>& words, int dict_len, word const* dict)
{
    int n = strlen(str);
    int* max_count = new int[n+1];
    int* max_split = new int[n+1];

    /**
     * 
     * max_count[i] = 1 + max { max_count[j] and str[j..i) is a valid word }
     *             j
     *
     * max_count[0] = 0
     *
     * we still have the choice of greedy or not if there are mulitple maximum values
     */

    max_count[0] = 0;
    max_split[0] = 0;
    
    for (int i = 1; i <=n; ++i) {
        max_count[i] = 0;
        max_split[i] = 0;
        
        int count = 0;
        int split;
        for (int j = 0; j < i; ++j) {
            word w(str+j, str+i);
            for (int k = 0; k < dict_len; ++k) {
                if (w == dict[k] && max_count[j] >= 0) {
                    if (max_count[j]+1 > count) {
                        count = max_count[j]+1;
                        split = j;
                    }
                }
            }
        }
        if (count > 0) {
            max_count[i] = count;
            max_split[i] = split;
        }
    }
   
    int count = max_count[n];

    /**
     * output the maximum options now
     */
    {
        int b;
        int e = n;
        while (max_split[e] >= 0) {
            b = max_split[e];
            word w(str+b, str+e);
            words.push_back(w);
            
            e = b;
            if (e == 0)
                break;
        }
    }

    delete[] max_count;
    delete[] max_split;
    return count;
}
