#include "words.h"

int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    char const* str = argv[1];
    int count = split_words_ways(str);
    printf("%d\n", count);
    return 0;
}

/**
 * 
 >./split-count.play abc
 4 

 a b c
 a bc
 ab c
 abc

 totally 4

 easy to expand to 2^(n-1) case
 * 
 */
