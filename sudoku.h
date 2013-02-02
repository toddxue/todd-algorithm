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
    inline bool backtrack1(int (&A)[9][9]) {
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
            if (check(A, row_choice, col_choice) && backtrack1(A))
                return true;
        }

        /**
         * if failed, restore status before try and backup to try other choices from higher level
         */
        A[row_choice][col_choice] = 0;
        return false;
    }


    /**
     * A little bit optimization, don't lookup from beginning
     * A little bit faster from 10 to 7, but not to 4,3, 
     */
    inline bool backtrack2(int (&A)[9][9], int row_curr = 0, int col_curr = 0) {
        /**
         * get next choice
         */
        bool has_choice = false;
        while (row_curr < 9 && col_curr < 9) {
            if (col_curr + 1 < 9)
                ++col_curr;
            else
                col_curr = 0, ++row_curr;
            
            if (row_curr < 9 && col_curr < 9 && A[row_curr][col_curr] == 0) {
                    has_choice = true;
                    break;
            }
        }
        
        /**
         * no further choice, to bottom, succeeded
         */
        if (has_choice == false)
            return true;
            
        /**
         * try the choice
         */
        int row_choice = row_curr;
        int col_choice = col_curr;
        for (int choice = 1; choice <= 9; ++choice) {
            A[row_choice][col_choice] = choice;
                
            /**
             * if try succeeded, return immediately
             */
            if (check(A, row_choice, col_choice) && backtrack2(A))
                return true;
        }

        /**
         * if failed, restore status before try and backup to try other choices from higher level
         */
        A[row_choice][col_choice] = 0;
        return false;
    }


    /**
     * now do a big jump on optimization, build the path first
     * a cell list order by increasing choices 
     * always iterate cell with less choice first, this matches the usually human experiences
     * 
     * return the length of the choices
     */
    inline int build_choice_cell_list(int (&A)[9][9], int* choices) {
        int row_weight[9] = {0};
        int col_weight[9] = {0};
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (A[row][col] == 0) {
                    row_weight[row]++;
                    col_weight[col]++;
                }
            }
        }

        int choices_c = 0;
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (A[row][col] == 0) {
                    int weight = row_weight[row] < col_weight[col] ? row_weight[row] : col_weight[col];
                    choices[choices_c++] =  (weight << 16) + (row << 8) + col;
                }
            }
        }
        return choices_c;
    }


    inline bool backtrack3(int (&A)[9][9], int curr, int choices_c, int* choices) {
        /**
         * get next choice
         */
        bool has_choice = false;
        if (curr + 1 < choices_c) {
            ++curr;
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
        int row_choice = (choices[curr] >> 8) & ((1<<8) - 1);
        int col_choice = (choices[curr]) & ((1<<8) - 1);
        for (int choice = 1; choice <= 9; ++choice) {
            A[row_choice][col_choice] = choice;
                
            /**
             * if try succeeded, return immediately
             */
            if (check(A, row_choice, col_choice) && backtrack3(A, curr, choices_c, choices))
                return true;
        }

        /**
         * if failed, restore status before try and backup to try other choices from higher level
         */
        A[row_choice][col_choice] = 0;
        return false;
    }

    inline bool backtrack3(int (&A)[9][9]) {
        int choices[9*9];
        int choices_c = build_choice_cell_list(A, choices);
        int curr = -1;
        return backtrack3(A, curr, choices_c, choices);
    }
    
}

#endif
