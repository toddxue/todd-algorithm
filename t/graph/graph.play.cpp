#include <stdio.h>
#include "graph.h"

/**
       0
     / | \
    1 -|- 2
     \ | /
       3 
 */
void K_4() {

    Graph g;
    Vertex v[] = {
        {40, 5, 0},
        {20, 15, 1},
        {60, 15, 2},
        {40, 25, 3},
    };
    
    for (int i = 0; i < 4; ++i) g.vertex(v+i);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (i < j)
                g.edge(v+i, v+j);

    g.print((char*)__func__);

    graph::Matrix gm(4);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            gm.edge(i, j) = (i != j);
    gm.print();

    graph::AdjList ga(4);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (i != j) ga.edge(i, j);
    ga.print();
}

/*
       1  2  3
        \ | /
         \|/
          .
         /|\
        / | \
       4  5  6
 */
void K_3_3() {
    Graph g;
    Vertex v1[3] = {
        {20, 10, 1},
        {40, 10, 2},
        {60, 10, 3},
    };

    Vertex v2[3] = {
        {20, 20, 4},
        {40, 20, 5},
        {60, 20, 6},
    };

    for (int i = 0; i < 3; ++i) {
        g.vertex(&v1[i]);
        g.vertex(&v2[i]);
    }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            g.edge(v1+i, v2+j);

    g.print((char*)__func__);

    graph::Matrix gm(7);
    for (int i = 1; i <= 3; ++i)
        for (int j = 4; j <= 6; ++j) {
            gm.edge(i, j) = 1;
            gm.edge(j, i) = 1;
        }
    gm.print();

    graph::AdjList ga(7);
    for (int i = 1; i <= 3; ++i)
        for (int j = 4; j <= 6; ++j) {
            ga.edge(i, j);
            ga.edge(j, i);
        }
    ga.print();
}

int main(int argc, char* argv[]) {

    K_4();
    K_3_3();

    graph::AdjList2 ga2(3, 3);
    ga2.print();
}
