#include "grids.h"

int main(int argc, char* argv[]) {
    int percentage = 100;
    if (argv[1]) 
        percentage = strtol(argv[1], 0, 10);

    Grids gr(percentage);
    gr.draw();
    gr.print();
}
