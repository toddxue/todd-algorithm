#include <string.h>
#include <stdio.h>
#include "common.h"
#include "palindrome.h"

int main(int argc, char* argv[]) {

    if (argc != 2)
        return 0;

    int n = strlen(argv[1]);
    char const* s = argv[1];
    char const* pb;
    char const* pe;
    int* buffer = new int[n];
    ARRMEM_GUARD(int, buffer);
    
    for (int i = 0; i < 1000; ++i) {
        palindrome::max_substr_Manacher(n, s, pb, pe, buffer);
        //palindrome::max_substr_center(n, s, pb, pe);
        //palindrome::max_substr_simple(n, s, pb, pe);
    }

    printf("%.*s\n", int(pe-pb), pb);
    return 0;
}

/**
 * $ ./palindrome.play 'Able was I ere I saw Elba'
 *  was I ere I saw
 */
