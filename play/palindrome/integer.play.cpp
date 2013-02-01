#include <string.h>
#include <stdio.h>
#include "common.h"
#include "palindrome.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 2)
        return 0;

    int n = strtol(argv[1], 0, 10);
    int m = palindrome::integer::closest_palindrome(n);
    printf("%d\n", m);

    return 0;
}

