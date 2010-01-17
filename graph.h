/*
 * graph.h --
 *
 * graph data structures and misc routines
 *
 * 2010/01/17: initial release by Todd Xue
 */

#ifndef _graph_h
#define _graph_h

struct Vertex {
    // draw support
    int x;
    int y;

    int no;
    int edges_c;
    void* data;
    struct Edge* edges[100];
};

struct Edge {
    int no;
    void* data;
    Vertex* from;
    Vertex* to;
};

struct Graph {
    int vertices_c;
    int edges_c;
    Vertex** vertices;
    Edge* edges;
    
    Graph() {
        vertices_c = 0;
        vertices = new Vertex*[100];
        
        edges_c = 0;
        edges = new Edge[10000];
    }
    ~Graph() {
        delete[] edges;
        delete[] vertices;
    }

    void print();

    void vertex(Vertex* v) { vertices[vertices_c++] = v; }
    void edge(Vertex* from, Vertex* to) {
        Edge* e = &edges[edges_c++];
        e->from = from;
        e->to = to;
        from->edges[from->edges_c++] = e;
    }

private: 
    Graph(Graph const&); 
    void operator = (Graph const&);
};

#endif
