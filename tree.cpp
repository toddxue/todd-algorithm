/*
 * tree.cpp --
 *
 * tree data structures and misc routines
 *
 * 2010/01/12: initial release by Todd Xue
 */

#include "tree.h"
#include "draw.h"

/*
 *-------------------------------------------------------------------------
 *
 * Tree::print --
 *      print tree, 2 questions to resolve
 *        1. tree height
 *        2. tree width
 *      after that, we can assign each node a coordinate (x,y)
 *        y is the node's height
 *        x is the node's right pos on same level  
 *      
 *      here
 *        y represented by level
 *        x represented by level_no 
 *      add these as member of Tree
 *  
 *      draw is done through Draw class
 *
 *      So the hardness is how to calculate the level_no:
 *         -- simply done throught the level_no_curr[MAX_LEVEL] array
 *
 *-------------------------------------------------------------------------
 */
void tree_calculate_level(Tree* t, int curr_level) {
    t->level = curr_level++;
    for (t = t->son; t; t = t->sib) 
        tree_calculate_level(t, curr_level);
}

void tree_calculate_level_no(Tree* t, int* level_no, int& level_max) {
    t->level_no = level_no[t->level];
    level_no[t->level]++;
    if (t->level > level_max)
        level_max = t->level;
    for (Tree* s = t->son; s; s = s->sib) 
        tree_calculate_level_no(s, level_no, level_max);
}

void tree_calculate_x(Tree* t, int* level_no) {
    int level_nodes = level_no[t->level];
    double unit = Draw::eX_MAX * 1.0/(level_nodes+1);
    t->x = int(round(unit * (1+t->level_no))); // [unit, ..., level_nodes*unit]
    for (Tree* s = t->son; s; s = s->sib) 
        tree_calculate_x(s, level_no);
}

void draw_tree(Tree* t, Draw& d, double yunit) {
    for (Tree* s = t->son; s; s = s->sib) {
        d.move_to(t->x, int(round(yunit*(1+t->level))));
        d.line_to(s->x, int(round(yunit*(1+s->level))));
    }
    for (Tree* s = t->son; s; s = s->sib) 
        draw_tree(s, d, yunit);
    d.out(t->x, int(round(yunit*(1+t->level))), t->no);
}

void Tree::print() {

    tree_calculate_level(this, 0);

    // calculate level_no 1st
    int level_no[64] = {0};
    int level_max = 0;
    tree_calculate_level_no(this, level_no, level_max);
    
    // calculate the x by the level_no
    tree_calculate_x(this, level_no);
    
    // now it's ready to print out
    Draw d;
    double yunit = Draw::eY_MAX * 1.0 / (level_max+2);
    draw_tree(this, d, yunit);
    d.print();
}

void preorder_print0(Tree* t) {
    printf("%d ", t->no);
    for (t = t->son; t; t = t->sib) 
        preorder_print0(t);
}

/*
 *-------------------------------------------------------------------------
 *
 * preorder_print --
 *      preorder tranverse
 * 
 * NOTES:
 *      stack has subtree-localness:
 *        when still in subtree, the stack above subtree is not touched
 *      
 *      still no strict math proof of this algorithm
 *
 *-------------------------------------------------------------------------
 */
void preorder_print(Tree* t) {
    /*
     * visit it when push it into stack
     * visit order is DFS
     */
    Tree* nodes[1024];
    int c = 0;
    goto inner;
    
    /*
     * assert: 
     *   top left sib visited
     *   recursive into top->sib
     *   top itself is popped out
     */
    while (c > 0) {
        t = nodes[--c]->sib;
    inner:
        for (; t; t = t->son) {
            printf("%d ", t->no);
            nodes[c++] = t;
        }
    }
}

/*
 *-------------------------------------------------------------------------
 *
 * next_tree --
 *      tree generation algorithm, this is an interesting algorithm, 
 *      even if it's not fast, there are a lot of papers decribing
 *      tree generation aglorithm in the last 40 years
 *
 * RETURN:
 *      true - re adjust tree to next one
 *      false - it's already the last tree
 *
 * PRE CONDTION:
 *      t != 0
 *
 *-------------------------------------------------------------------------
 */
void reset_tree(Tree* t);
bool next_tree(Tree* t) {
    if (t->son == 0) 
        return false;

    for (Tree* s = t->son; s; s = s->sib) {
        if (next_tree(s)) {
            for (Tree* s2 = t->son; s2 != s; s2 = s2->sib) {
                reset_tree(s2);
            }
            return true;
        }
    }

    Tree* s = t->son;
    while (s && s->son == 0) 
        s = s->sib;

    if (s == 0) 
        return false; // already the last one

    reset_tree(s);
    Tree* extract = s->son;
    s->son = extract->son;
    extract->son = 0;
    
    if (s->sib == 0) 
        s->sib = extract;
    else {
        s = s->sib;
        if (s->son) 
            reset_tree(s);
        Tree* tmp = s->son;
        s->son = extract;
        extract->son = tmp;
    }
    return true;
}

/*
 * reset t to a single path, actually it's DFS sequence path
 */
void reset_tree(Tree* t) {
    Tree* s_sib;
    for (Tree* s = t->son; s; s = s_sib) {
        s_sib = s->sib;

        if (s->son) reset_tree(s);
        t->son = s;
        t = t->son;
        t->sib = 0;
        while (t->son) t = t->son;
    }
}


/*
 *-------------------------------------------------------------------------
 *
 * tree_preorder --
 *      preorder tranverse
 *
 * PRE CONDTION:
 *      suppose n = number of vertices of tree t
 *      o must at least contain n integers
 * 
 * NOTE:
 *      the codes becomes obvious when we use the path concept
 *      every path of tree is visited from leftest path to rigthtest
 * 
 *-------------------------------------------------------------------------
 */
void tree_preorder(Tree* t, int* o) {

    int o_fill = 0;
    Tree* nodes[1024];
    int c = 0;
    goto inner;
    
    while (c > 0) {
        t = nodes[--c]->sib;
    inner:
        for (; t; t = t->son) {
            o[o_fill++] = t->no;
            if (t->sib)
                nodes[c++] = t;
        }
    }
}

void tree_preorder_recursive_internal(Tree* t, int*& o) {
    *o++ = t->no;
    for (t = t->son; t; t = t->sib)
        tree_preorder_recursive_internal(t, o);
}
void tree_preorder_recursive(Tree* t, int* o) {
    tree_preorder_recursive_internal(t, o);
}

