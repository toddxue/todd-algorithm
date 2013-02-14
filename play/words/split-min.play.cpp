#include "words.h"

static word dict[] = { "a", "b", "c", "ab", "bc", "abc"};

int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    char const* str = argv[1];
    std::vector<word> words;
    
    int count = split_minimum_words(str, words, sizeof(dict)/sizeof(dict[0]), dict);
    if (count > 0) {
        printf("count=%d\n", count);
        for (int i = 0; i < words.size(); ++i)
            fprintf(stdout, "%.*s\n", words[i].len(), words[i].b);
        return 0;
    }
    else
        return 2;
}

/**
 * 
 >./split-min.play aababcaba
 count=5
 a
 ab
 abc
 ab
 a
 * 
 */
