/*
 * tree.h --
 *
 * tree data structures and misc routines
 *
 * 2010/01/12: initial release by Todd Xue
 */

#ifndef _tree_h
#define _tree_h

struct Tree {
    int no;
    void* data;
    Tree* sib;
    Tree* son;

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
void Tree_root(Tree* t, int no) { t->level = 0; t->sib = t->son = 0; t->no = no; }

inline 
void Tree_parent_son(Tree* parent, Tree* son, int no) { 
    son->level = parent->level+1;
    son->son = son->sib = 0;
    if (!parent->son)
        parent->son = son;
    else {
        Tree* t = parent->son;
        while (t->sib) t = t->sib;
        t->sib = son;
    }
    son->no = no;
}
#endif
