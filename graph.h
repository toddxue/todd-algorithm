/*
 * graph.h --
 *
 * graph data structures and misc routines
 *
 * 2010/01/17: initial release by Todd Xue
 */

#ifndef _graph_h
#define _graph_h

#include <stdio.h>

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

    void print(char* title = 0);

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

namespace graph {
    struct Matrix {
        void** _data;
        int* matrix;
        int dim;
        Matrix(int dim) : dim(dim) {
            _data = new void* [dim];
            matrix = new int [dim*dim];
        }
        ~Matrix() {
            delete[] matrix;
            delete[] _data;
        }

        int& edge(int i, int j) { return matrix[i*dim + j]; }
        void*& data(int i) { return _data[i]; }

        void print() {
            for (int i = 0; i < dim; ++i) {
                for (int j = 0; j < dim; ++j) 
                    printf("%2d ", edge(i, j));
                printf("\n");
            }
        }
    
    private:
        Matrix(Matrix const&);
        void operator = (Matrix const&);
    };

    struct AdjList {
        struct A;
        struct V {
            void* data;
            A* adjs;
        };
        struct A {
            A* next;
            void* data;
            int vno;
            A* free_next;
        };
        A* free_head;

        int dim;
        V* varr;
        AdjList(int dim) : free_head(0), dim(dim) { 
            varr = new V[dim]; 
            for (int i = 0; i < dim; ++i)
                varr[i].adjs = 0;
        }
        ~AdjList() { 
            while (free_head) {
                A* free = free_head;
                free_head = free->free_next;
                delete free;
            }
            delete[] varr;
        }

        void edge(int i, int j) {
            A* a = new A;
            a->free_next = free_head;
            free_head = a;

            a->vno = j;
            a->next = varr[i].adjs;
            varr[i].adjs = a;
        }
        
        void print() {
            for (int i = 0; i < dim; ++i) {
                printf("%2d :", i);
                for (A* a = varr[i].adjs; a; a = a->next) 
                    printf(" %2d", a->vno);
                printf("\n");
            }
        }
        
    private:
        AdjList(AdjList const&);
        void operator = (AdjList const&);
    };

    struct AdjList2 {
        int* arr;
        int dim;
        int e;
        AdjList2(int dim, int e) : dim(dim), e(e) {
            arr = new int[dim + 1 + e * 2];
            for (int i = 0; i <= dim; ++i)
                arr[i] = 0;
        }
        ~AdjList2() {
            delete[] arr;
        }
        void print() {
            for (int i = 0; i < dim; ++i) {
                printf("%2d :", i);
                for (int j = arr[i]; j < arr[i+1]; ++j)
                    printf(" %2d", arr[j]);
                printf("\n");
            }
        }
    private:
        AdjList2(AdjList2 const&);
        void operator = (AdjList2 const&);
    };
}

#endif
