#include "grids.h"
#include <queue>

void Grids::BFS()
{
    bool visited[10][5] = {0};
    std::queue<Vertex*> q;

    q.push(&vertices[0][0]);
    visited[0][0] = true;
    
    Vertex* v;
    Vertex* v_to;
    Edge* e;

    d.fill_x = '~';
    d.fill_y = '.';

    while (q.size() > 0) {
        v = q.front();
        q.pop();

        for (int i = 0; i < v->edges_c; ++i) {
            e = v->edges[i];
            v_to = e->to;
            if (!visited[v_to->x][v_to->y]) {
                q.push(v_to);
                visited[v_to->x][v_to->y] = true;
                d.move_to(v->x, v->y);
                d.line_to(v_to->x, v_to->y);
            }
        }
    }
}

void Grids::DFS()
{
}



