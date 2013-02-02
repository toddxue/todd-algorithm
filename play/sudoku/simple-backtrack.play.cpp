#include "sudoku.h"

int main() {

    int M1[9][9] = 
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

    int M2[9][9] = 
        {
            {8, 0, 3,  5, 0, 0,  0, 0, 0},
            {0, 0, 0,  2, 0, 9,  0, 1, 0},
            {0, 0, 6,  8, 0, 0,  3, 0, 0},

            {0, 3, 0,  0, 0, 0,  6, 5, 0},
            {0, 9, 0,  0, 4, 0,  0, 8, 0},
            {0, 5, 4,  0, 0, 0,  0, 2, 0},

            {0, 0, 9,  0, 0, 3,  2, 0, 0},
            {0, 8, 0,  4, 0, 2,  0, 0, 0},
            {0, 0, 0,  0, 0, 8,  1, 0, 9},
        };

    int M3[9][9] = 
        {
            {0, 8, 0,  6, 9, 0,  1, 0, 0},
            {6, 0, 0,  5, 0, 0,  9, 0, 0},
            {0, 0, 0,  0, 0, 0,  0, 0, 4},

            {0, 0, 0,  0, 0, 3,  6, 0, 5},
            {7, 3, 0,  0, 0, 0,  0, 9, 2},
            {5, 0, 2,  8, 0, 0,  0, 0, 0},

            {8, 0, 0,  0, 0, 0,  0, 0, 0},
            {0, 0, 4,  0, 0, 6,  0, 0, 7},
            {0, 0, 1,  0, 3, 4,  0, 8, 0},
        };


    for (int c = 0; c < 10; ++c) {
        int A[9][9];
        memcpy(A, M3, sizeof(A));
        if (sudoku::backtrack1(A)) {
            sudoku::print(A);
            int r,l;
            if (!sudoku::checkall(A, r, l)) {
                fprintf(stderr, "internal error at (%d, %d)\n", r, l);
                return 1;
            }
            return 0;
        }
    }

    return 1;
}

