#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char* argv[]) {

    int n = argv[1] ? strtol(argv[1], 0, 10) : 5;
    
    Tree* trees = new Tree[n]; 
    Tree_root(&trees[0], 0);
    for (int i = 1; i < n; ++i)
        Tree_parent_son(&trees[i-1], &trees[i], i);

    int total = 0;
    Tree& root = trees[0];
    ++total;
    root.print(); printf("\n");
    while (next_tree(&root))  {
        ++total;
        root.print(); printf("\n");
    }
    delete[] trees;
    printf("total %d trees\n", total);
    fprintf(stderr, "total %d trees\n", total);
    return 0;
}

