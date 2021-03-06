/*
 * grids.h --
 *
 * grids data structures and misc routines
 *
 * 2010/01/17: initial release by Todd Xue
 */

#ifndef _grids_h
#define _grids_h

/**
 * A grid graph to prepare for interesting algorithm visualization
 * Will always be 9x9 grids cell right now
 * 
 *   
   4  |
      .
   2  |
   1  |
   0  |_ _ ... _|
      0 1     9
 * 
 * 
 */

#include "graph.h"
#include "draw.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Grids {
    Graph g;
    Vertex vertices[10][5];
    Draw d;

    Grids(int percent = 100, bool diag = true, bool bidirect = true) : d(false, '-', '|')
    {
        int curr_no = 0;

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 5; ++j) {

                vertices[i][j].no = curr_no++;
                vertices[i][j].x  = i * 10;
                vertices[i][j].y  = j * 7;
                vertices[i][j].edges_c = 0;

                g.vertex(&vertices[i][j]);

                if (i > 0) edge(&vertices[i-1][j], &vertices[i][j], percent, bidirect);
                if (j > 0) edge(&vertices[i][j-1], &vertices[i][j], percent, bidirect);
                if (i > 0 && j > 0 && diag)
                    edge(&vertices[i-1][j-1], &vertices[i][j], percent, bidirect);
            }
        }
    }

    void edge(Vertex* from, Vertex* to, int percent, bool bidirect) {
        if (random() % 100 < percent) {
            g.edge(from, to);
            if (bidirect)
                g.edge(to, from);
        }
    }
    
    void draw(char fill_x = '-', char fill_y = '|', char fill_backslash = '\\')
    {
        d.fill_x = fill_x;
        d.fill_y = fill_y;
        d.fill_backslash = fill_backslash;
        
        g.draw(d);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 5; ++j) {
                Vertex* v = &vertices[i][j];
                d.out(v->x, v->y, 'o');
            }
        }
    }

    void print() { 
        d.print(); 
    }

    void BFS(int startX, int startY);

    void DFS(int x, int y);
    void DFS(Vertex* v);
};

#endif
