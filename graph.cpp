/*
 * graph.cpp --
 *
 * graph data structures and misc routines
 *
 * 2010/01/17: initial release by Todd Xue
 */

#include "graph.h"
#include "draw.h"

/*
 *-------------------------------------------------------------------------
 *
 *  Graph::print --
 *        print the graph
 *
 *-------------------------------------------------------------------------
 */
void Graph::print() {
    Draw d;
    for (int i = 0; i < vertices_c; ++i) {
        Vertex* v = vertices[i];
        for (int j = 0; j < v->edges_c; ++j) {
            Vertex* w = v->edges[j]->to;
            d.move_to(v->x, v->y);
            d.line_to(w->x, w->y);
        }
    }
    for (int i = 0; i < vertices_c; ++i) {
        Vertex* v = vertices[i];
        d.out(v->x, v->y, v->no);
    }

    d.print();
}

