#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "TAP.h"

static const int catalan[] =  { 
    1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 
    742900, 2674440, 9694845
};

bool check(int n) {
    Binary_Tree* binary_trees = new Binary_Tree[n]; 
    Binary_Tree_root(&binary_trees[0], 0);
    for (int i = 1; i < n; ++i)
        Binary_Tree_parent_left(&binary_trees[i-1], &binary_trees[i], i);

    int total = 0;
    Binary_Tree& root = binary_trees[0];
    ++total;
    while (next_binary_tree(&root))
        ++total;
    delete[] binary_trees;
    
    return total == catalan[n];
}

int main(int argc, char* argv[]) {
    OK_SUM();

    OK(check(1));
    OK(check(2));
    OK(check(3));
    OK(check(4));
    OK(check(5));
    OK(check(6));
    OK(check(7));
    OK(check(8));
    OK(check(9));
    OK(check(10));
    OK(check(11));
    OK(check(12));
    OK(check(13));
    OK(check(14));
    return 0;
}

