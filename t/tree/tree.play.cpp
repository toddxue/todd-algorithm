#include "tree.h"

int main(int argc, char* argv[]) {
    
    Tree root;
    Tree left;
    Tree middle;
    Tree right;
    
    Tree_root(&root, 'a');
    Tree_parent_son(&root, &left, 'b');
    Tree_parent_son(&root, &middle, 'c');
    Tree_parent_son(&root, &right, 'd');

    Tree ll_1;
    Tree ll_2;
    Tree_parent_son(&left, &ll_1, 'e');
    Tree_parent_son(&left, &ll_2, 'f');

    Tree rr_1;
    Tree rr_2;
    Tree_parent_son(&right, &rr_1, 'g');
    Tree_parent_son(&right, &rr_2, 'h');

    Tree mm_1;
    Tree mm_2;
    Tree_parent_son(&middle, &mm_1, 'i');
    Tree_parent_son(&middle, &mm_2, 'j');

    Tree e1, e2;
    Tree_parent_son(&ll_1, &e1, 'k');
    Tree_parent_son(&ll_1, &e2, 'l');
    
    root.print();

    return 0;
}

