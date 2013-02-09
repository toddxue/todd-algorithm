#include "grids.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    Grids gr;
    if (argc != 3) {
        return 1;
    }

    int start_x = strtol(argv[1], 0, 10);
    int start_y = strtol(argv[2], 0, 10);

    gr.draw(' ', ' ');
    gr.BFS(start_x, start_y);
    gr.print();
}
