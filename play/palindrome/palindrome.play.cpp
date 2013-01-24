#include "palindrome.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    if (argc != 2)
        return 0;

    char const* pb;
    char const* pe;
    
    palindrome::max_substr_center(strlen(argv[1]), argv[1], pb, pe);

    printf("%.*s\n", int(pe-pb), pb);
    return 0;
}

/**
 * $ ./palindrome.play 'Able was I ere I saw Elba'
 *  was I ere I saw
 */
