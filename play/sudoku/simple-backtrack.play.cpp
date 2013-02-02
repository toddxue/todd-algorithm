#include "sudoku.h"

int main() {

    int A[9][9] = 
        {
            {0, 9, 0,  0, 3, 4,  1, 0, 5},
            {0, 0, 6,  0, 2, 0,  0, 0, 8},
            {7, 0, 5,  0, 0, 6,  0, 0, 2},

            {0, 0, 1,  0, 8, 0,  0, 4, 0},
            {5, 0, 2,  0, 4, 0,  3, 0, 1},
            {0, 3, 0,  0, 1, 2,  5, 0, 0},

            {1, 0, 0,  2, 0, 0,  8, 0, 9},
            {8, 0, 0,  0, 7, 0,  6, 0, 0},
            {6, 0, 9,  4, 5, 0,  0, 1, 0},
        };

    if (sudoku::simple_backtrack(A)) {
        sudoku::print(A);
        int r,l;
        if (!sudoku::checkall(A, r, l)) {
            fprintf(stderr, "internal error at (%d, %d)\n", r, l);
            return 1;
        }
        return 0;
    }

    return 1;
}
