#include "words.h"

int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    char const* str = argv[1];
    std::vector<word> words;
    if (split_words(str, words)) {
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
