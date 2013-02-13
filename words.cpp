#include "words.h"

/**
 * split string into words
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
