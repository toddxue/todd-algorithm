#include <stdio.h>
#include "tree.h"

int main(int argc, char* argv[]) {
    
    Tree root;
    Tree left;
    Tree middle;
    Tree right;
    
    Tree_root(&root, 1);
    Tree_parent_son(&root, &left, 2);
    Tree_parent_son(&root, &middle, 3);
    Tree_parent_son(&root, &right, 4);

    Tree ll_1;
    Tree ll_2;
    Tree_parent_son(&left, &ll_1, 5);
    Tree_parent_son(&left, &ll_2, 6);

    Tree rr_1;
    Tree rr_2;
    Tree_parent_son(&right, &rr_1, 7);
    Tree_parent_son(&right, &rr_2, 8);

    Tree mm_1;
    Tree mm_2;
    Tree_parent_son(&middle, &mm_1, 9);
    Tree_parent_son(&middle, &mm_2, 10);

    Tree e1, e2;
    Tree_parent_son(&ll_1, &e1, 11);
    Tree_parent_son(&ll_1, &e2, 12);
    
    root.print();
    preorder_print0(&root); printf("\n");
    preorder_print(&root); printf("\n");

    {
        int no = 1;
        Tree trees[64] = {0};
        Tree_root(&trees[1], 1);
        for (int i = 2; i < 64; ++i)
            Tree_parent_son(&trees[i/2], &trees[i], i);
        trees[1].print();
        preorder_print0(&trees[1]); printf("\n");
        preorder_print(&trees[1]); printf("\n");
    }

    return 0;
}

