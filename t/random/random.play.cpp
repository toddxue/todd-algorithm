#include "random.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int len = argc-1;
    int* a = new int[len];
    for (int i = 1; i < argc; ++i)
        a[i-1] = strtol(argv[i], 0, 10);

    random_permutation(len, a);
    for (int i = 0; i < len; ++i)
        fprintf(stdout, "%d ", a[i]);
    fprintf(stdout, "\n");
    
    delete a;
    return 0;
}
