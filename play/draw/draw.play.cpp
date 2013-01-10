#include "draw.h"

int main(int argc, char* argv[]) {
    Draw d;
    
    d.move_to(10, 10);
    d.line_to(20, 10);
    d.line_to(15, 15);
    d.line_to(10, 10);

    d.out(20, 10, 111);
    d.out(15, 15, 222);
    d.out(10, 10, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzuuuuuuuuuuuuuuuu");
    

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

