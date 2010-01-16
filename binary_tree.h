/*
 * binary_tree.h --
 *
 * binary_tree data structures and misc routines
 *
 * 2010/01/12: initial release by Todd Xue
 */

#ifndef _binary_tree_h
#define _binary_tree_h

struct Binary_Tree {
    int no;
    void* data;
    Binary_Tree* left;
    Binary_Tree* right;

    /*
     * the 1st question: how to print it
     */
    void print();

    /*
     * helper data to support print
     */
    int level;
    int level_no;
    int x;
};

inline 
void Binary_Tree_root(Binary_Tree* t, int no) { t->left = t->right = 0; t->no = no; }

inline 
void Binary_Tree_parent_left(Binary_Tree* parent, Binary_Tree* son, int no) { 
    son->no = no;
    parent->left = son;
    son->left = son->right = 0; 
}

inline 
void Binary_Tree_parent_right(Binary_Tree* parent, Binary_Tree* son, int no) { 
    son->no = no;
    parent->right = son;
    son->left = son->right = 0; 
}

void reset_binary_tree(Binary_Tree* t);
bool next_binary_tree(Binary_Tree* t);

#endif
