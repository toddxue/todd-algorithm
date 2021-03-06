#include "words.h"

static word dict[] = { "a", "an", "em", "fir", "fire", "ire", "ma", "man" };

int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    char const* str = argv[1];
    std::vector<word> words;
    if (split_words(str, words, sizeof(dict)/sizeof(dict[0]), dict)) {
        for (int i = 0; i < words.size(); ++i)
            fprintf(stdout, "%.*s\n", words[i].len(), words[i].b);
        return 0;
    }
    else
        return 2;
}

/**
 * 

 $ ./split.play fireman
 fir
 em
 an

 * 
 */
