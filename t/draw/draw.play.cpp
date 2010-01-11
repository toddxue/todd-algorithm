#include "draw.h"

int main(int argc, char* argv[]) {
    Draw d;
    
    d.move_to(10, 10);
    d.line_to(20, 10);
    d.line_to(15, 15);
    d.line_to(10, 10);

    d.point(20, 10) = 'o';
    d.point(15, 15) = 'o';
    d.point(10, 10) = 'o';
    

    d.move_to(20, 20);
    d.line_to(20, 29);
    d.line_to(60, 29);
    d.line_to(60, 20);
    d.line_to(20, 20);
//     d.line_to(20, 20);
//     d.line_to(10, 10);

    d.print();
    return 0;
}

