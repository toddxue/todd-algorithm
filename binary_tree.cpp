/*
 * binary_tree.cpp --
 *
 * binary_tree data structures and misc routines
 *
 * 2010/01/12: initial release by Todd Xue
 */

#include "binary_tree.h"
#include "draw.h"

/*
 *-------------------------------------------------------------------------
 *
 * Binary_Tree::print --
 *      print binary_tree, 2 questions to resolve
 *        1. binary_tree height
 *        2. binary_tree width
 *      after that, we can assign each node a coordinate (x,y)
 *        y is the node's height
 *        x is the node's right pos on same level  
 *      
 *      here
 *        y represented by level
 *        x represented by level_no 
 *      add these as member of Binary_Tree
 *  
 *      draw is done through Draw class
 *
 *      So the hardness is how to calculate the level_no:
 *         -- simply done throught the level_no_curr[MAX_LEVEL] array
 *
 *-------------------------------------------------------------------------
 */
void binary_tree_calculate_level(Binary_Tree* t, int curr_level) {
    t->level = curr_level++;
    if (t->left) 
        binary_tree_calculate_level(t->left, curr_level);
    if (t->right) 
        binary_tree_calculate_level(t->right, curr_level);
}

void binary_tree_calculate_level_no(Binary_Tree* t, int& level_max) {
    if (t->level > level_max)
        level_max = t->level;
    if (t->left) {
        t->left->level_no = t->level_no * 2;
        binary_tree_calculate_level_no(t->left, level_max);
    }
    if (t->right) {
        t->right->level_no = t->level_no * 2 + 1;
        binary_tree_calculate_level_no(t->right, level_max);
    }
}

void binary_tree_calculate_x(Binary_Tree* t) {
    int level_nodes = 1 << t->level;
    double unit = Draw::eX_MAX * 1.0/(level_nodes+1);
    t->x = int(round(unit * (1+t->level_no))); // [unit, ..., level_nodes*unit]
    if (t->left)
        binary_tree_calculate_x(t->left);
    if (t->right)
        binary_tree_calculate_x(t->right);
}

void draw_binary_tree(Binary_Tree* t, Draw& d, double yunit) {
    Binary_Tree* s;
    if ((s = t->left)) {
        d.move_to(t->x, int(round(yunit*(1+t->level))));
        d.line_to(s->x, int(round(yunit*(1+s->level))));
    }
    if ((s = t->right)) {
        d.move_to(t->x, int(round(yunit*(1+t->level))));
        d.line_to(s->x, int(round(yunit*(1+s->level))));
    }
    if ((s = t->left))
        draw_binary_tree(s, d, yunit);
    if ((s = t->right))
        draw_binary_tree(s, d, yunit);

    d.out(t->x, int(round(yunit*(1+t->level))), t->no);
}

void Binary_Tree::print() {

    binary_tree_calculate_level(this, 0);

    // calculate level_no 1st
    int level_max = 0;
    this->level_no = 0;
    binary_tree_calculate_level_no(this, level_max);
    
    // calculate the x by the level_no
    binary_tree_calculate_x(this);
    
    // now it's ready to print out
    Draw d;
    double yunit = Draw::eY_MAX * 1.0 / (level_max+2);
    draw_binary_tree(this, d, yunit);
    d.print();
}

/*
 *-------------------------------------------------------------------------
 *
 * next_binary_tree --
 *      binary_tree generation algorithm, this is an interesting algorithm, 
 *      even if it's not fast, there are a lot of papers decribing
 *      binary_tree generation aglorithm in the last 40 years
 *
 * RETURN:
 *      true - re adjust binary_tree to next one
 *      false - it's already the last binary_tree
 *
 * PRE CONDTION:
 *      t != 0
 *
 *-------------------------------------------------------------------------
 */
void reset_binary_tree(Binary_Tree* t);
bool next_binary_tree(Binary_Tree* t) {
    if (t->left) {
        if (next_binary_tree(t->left))
            return true;
        
        if (t->right) {
            if (next_binary_tree(t->right)) {
                if (t->left)
                    reset_binary_tree(t->left);
                return true;
            }
            else {
                reset_binary_tree(t->left);
                Binary_Tree* extract = t->left;
                t->left = extract->left;

                reset_binary_tree(t->right);
                extract->left = t->right;
                t->right = extract;
                return true;
            }
        }
        else {
            reset_binary_tree(t->left);
            Binary_Tree* extract = t->left;
            t->left = extract->left;

            extract->left = t->right;
            t->right = extract;
            return true;
        }
    }
    else {
        if (!t->right)
            return false;
        else
            return next_binary_tree(t->right);
    }
}

/*
 * reset t to a single path, actually it's DFS sequence path
 */
void reset_binary_tree(Binary_Tree* t) {
    if (t->left) {
        reset_binary_tree(t->left);
        if (t->right) {
            reset_binary_tree(t->right);
            Binary_Tree* s = t->left;
            while (s->left)
                s = s->left;
            s->left = t->right;
            t->right = 0;
        }
    }
    else {
        if (t->right) {
            reset_binary_tree(t->right);
            t->left = t->right;
            t->right = 0;
        }
    }
}
