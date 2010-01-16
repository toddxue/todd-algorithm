#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int main(int argc, char* argv[]) {

    int n = argv[1] ? strtol(argv[1], 0, 10) : 5;
    
    Binary_Tree* binary_trees = new Binary_Tree[n]; 
    Binary_Tree_root(&binary_trees[0], 0);
    for (int i = 1; i < n; ++i) {
        Binary_Tree_parent_left(&binary_trees[i-1], &binary_trees[i], i);
    }

    Binary_Tree& root = binary_trees[0];

    int total = 0;
    do  {
        ++total;
        root.print(); printf("\n");
    }
    while (next_binary_tree(&root));

    delete[] binary_trees;

    // now total is catalan_number(n)
    // the 1st 15 catalan nubmers are:
    // 1 2 5 14 42 132 429 1430 4862 16796 58786 208012 742900 2674440 9694845 
    
    printf("total %d binary_trees\n", total);
    fprintf(stderr, "total %d binary_trees\n", total);
    return 0;
}

