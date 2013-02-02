/*
 * knapsack.h --
 *
 * algorithms related to the calculation of the sudoku
 *
 * Fri Feb  1 16:12:15 PST 2013: initial release by Todd Xue
 */

#ifndef _sudoku_h
#define _sudoku_h

#include "common.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/**
 * some sudoku operations
 * backtracking and heuristic
 */

namespace sudoku {

    /**
     * to focus the problem itself, always using a global static matrix memory
     */
    inline void print(int (&A)[9][9]) {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col)
                printf("%2d  ", A[row][col]);
            printf("\n");
        }
    }

    /**
     * check if a certain number is accpetable
     */
    inline bool check(int (&A)[9][9], int i, int j) {

        //  1. Number can appear only once on each row: 
        for (int col = 0; col < 9; ++col)
            if (col != j && A[i][col] == A[i][j])
                return false;

        //  2. Number can appear only once on each column: 
        for (int row = 0; row < 9; ++row)
            if (row != i && A[row][j] == A[i][j])
                return false;

        // 3. Number can appear only once on each region: 
        int row_i = 3 * (i / 3);
        int col_j = 3 * (j / 3);
        for (int row = row_i; row < row_i + 3; ++row)
            for (int col = col_j; col < col_j + 3; ++col)
                if ((!(i == row && j == col)) && A[row][col] == A[i][j])
                    return false;
        
        return true;
    }
    
    inline bool checkall(int (&A)[9][9], int& r, int& l) {
        for (int row = 0; row < 9; ++row)
            for (int col = 0; col < 9; ++col)
                if (!check(A, row, col)) {
                    r = row;
                    l = col;
                    return false;
                }
        return true;
    }

    /**
     * Simplest backtrack
     */
    inline bool simple_backtrack(int (&A)[9][9]) {
        /**
         * get next choice
         */
        bool has_choice = false;
        int row_choice = -1, col_choice = -1;
        for (int row = 0; row < 9; ++row)
            for (int col = 0; col < 9; ++col)
                if (A[row][col] == 0) {
                    row_choice = row;
                    col_choice = col;
                    has_choice = true;
                }
        
        /**
         * no further choice, to bottom, succeeded
         */
        if (has_choice == false)
            return true;
            
        /**
         * try the choice
         */
        for (int choice = 1; choice <= 9; ++choice) {
            A[row_choice][col_choice] = choice;
                
            /**
             * if try succeeded, return immediately
             */
            if (check(A, row_choice, col_choice) && simple_backtrack(A))
                return true;
        }

        /**
         * if failed, restore status before try and backup to try other choices from higher level
         */
        A[row_choice][col_choice] = 0;
        return false;
    }
}

#endif
