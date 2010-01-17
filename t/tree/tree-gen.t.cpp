#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "TAP.h"

static const int catalan[] =  { 
    1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 
    742900, 2674440, 9694845
};

bool check(int n) {
    Tree* trees = new Tree[n]; 
    Tree_root(&trees[0], 0);
    for (int i = 1; i < n; ++i)
        Tree_parent_son(&trees[i-1], &trees[i], i);

    int total = 0;
    Tree& root = trees[0];
    ++total;
    while (next_tree(&root))
        ++total;
    delete[] trees;
    
    return total == catalan[n-1];
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

