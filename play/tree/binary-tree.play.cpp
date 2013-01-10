#include <stdio.h>
#include "binary_tree.h"

int main(int argc, char* argv[]) {
    
    Binary_Tree root;
    Binary_Tree left;
    Binary_Tree right;
    
    Binary_Tree_root(&root, 1);
    Binary_Tree_parent_left(&root, &left, 2);
    Binary_Tree_parent_right(&root, &right, 3);

    Binary_Tree ll_1;
    Binary_Tree ll_2;
    Binary_Tree_parent_left(&left, &ll_1, 4);
    Binary_Tree_parent_right(&left, &ll_2, 5);

    Binary_Tree rr_1;
    Binary_Tree rr_2;
    Binary_Tree_parent_left(&right, &rr_1, 6);
    Binary_Tree_parent_right(&right, &rr_2, 7);

    Binary_Tree e1, e2;
    Binary_Tree_parent_left(&ll_1, &e1, 8);
    Binary_Tree_parent_right(&ll_1, &e2, 9);
    
    root.print();
    return 0;
}

