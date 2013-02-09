#include "grids.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int percent = argc >= 2 && argv[1] ? strtol(argv[1], 0, 10) : 100;
    int start_x = argc >= 3 && argv[2] ? strtol(argv[2], 0, 10) : 0;
    int start_y = argc >= 4 && argv[3] ? strtol(argv[3], 0, 10) : 0;

    Grids gr(percent, true);
    //gr.draw();
    //gr.print();

    gr.draw(' ', ' ', ' ');
    gr.DFS(start_x, start_y);
    gr.print();
}
