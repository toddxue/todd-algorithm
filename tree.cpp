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
void calculate_level_no(Tree* t, int* level_no, int& level_max) {
    t->level_no = level_no[t->level];
    level_no[t->level]++;
    if (t->level > level_max)
        level_max = t->level;
    for (Tree* s = t->son; s; s = s->sib) 
        calculate_level_no(s, level_no, level_max);
}

void calculate_x(Tree* t, int* level_no) {
    int level_nodes = level_no[t->level];
    double unit = Draw::eX_MAX * 1.0/(level_nodes+1);
    t->x = int(round(unit * (1+t->level_no))); // [unit, ..., level_nodes*unit]
    for (Tree* s = t->son; s; s = s->sib) 
        calculate_x(s, level_no);
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
    // calculate level_no 1st
    int level_no[64] = {0};
    int level_max = 0;
    calculate_level_no(this, level_no, level_max);
    
    // calculate the x by the level_no
    calculate_x(this, level_no);
    
    // now it's ready to print out
    Draw d;
    double yunit = Draw::eY_MAX * 1.0 / (level_max+2);
    draw_tree(this, d, yunit);
    d.print();
}
