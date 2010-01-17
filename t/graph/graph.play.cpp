#include <stdio.h>
#include "graph.h"

int main(int argc, char* argv[]) {
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

    g.print();
    return 0;
}
