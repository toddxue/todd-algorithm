#include "grids.h"
#include <queue>

void Grids::BFS(int startX, int startY)
{
    bool visited[10*5] = {0};
    std::queue<Vertex*> q;
    std::vector<Vertex*> result;

    Vertex* v;
    Vertex* v_to;
    Edge* e;

    d.fill_x = '-';
    d.fill_y = '|';
    d.fill_backslash = '\\';

    v = &vertices[startX][startY];
    q.push(v);
    visited[v->no] = true;
    result.push_back(v);

    while (q.size() > 0) {
        v = q.front();
        q.pop();

        for (int i = 0; i < v->edges_c; ++i) {
            e = v->edges[i];
            v_to = e->to;
            if (!visited[v_to->no]) {
                q.push(v_to);
                visited[v_to->no] = true;
                result.push_back(v_to);

                d.move_to(v->x, v->y);
                d.line_to(v_to->x, v_to->y);
            }
        }
    }

    for (int i = 0; i < result.size(); ++i)
        d.out(result[i]->x, result[i]->y, i);
}

bool DFS_visited[10*5] = {0};
std::vector<Vertex*> DFS_result;

void Grids::DFS(int x, int y)
{
    d.fill_x = '-';
    d.fill_y = '|';
    d.fill_backslash = '\\';
    DFS(&vertices[x][y]);
    for (int i = 0; i < DFS_result.size(); ++i)
        d.out(DFS_result[i]->x, DFS_result[i]->y, i);
}

void Grids::DFS(Vertex* v)
{
    Vertex* v_to;
    Edge* e;

    DFS_visited[v->no] = true;
    DFS_result.push_back(v);

    for (int i = 0; i < v->edges_c; ++i) {
        e = v->edges[i];
        v_to = e->to;
        if (!DFS_visited[v_to->no]) {
            d.move_to(v->x, v->y);
            d.line_to(v_to->x, v_to->y);
            
            DFS(v_to);
        }
    }
    //DFS_result.push_back(v);
}



