/*
 * expr.cpp --
 *
 * stack based expr parse/calculation
 *
 * 2010/01/10: initial release by Todd Xue
 */

#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "expr.h"

/*
 *-------------------------------------------------------------------------
 *
 * expr --
 *
 * RETURN:
 *      the expr value
 *
 *-------------------------------------------------------------------------
 */

static int left_prec[256];
static int right_prec[256];

struct PrecInit {
    PrecInit() {

        struct PREC {
            char ch;
            int prec;
        };
        
        PREC l[] = {
            { '(', 10 },
            { '+', 20 },
            { '-', 20 },
            { '*', 30 },
            { '/', 30 },
            { '^', 40 },
            { ')', 1000 },
        };
        for (int i = 0; i < sizeof(l)/sizeof(PREC); ++i)
            left_prec[l[i].ch] = l[i].prec;

        PREC r[] = {
            { ')', 10 },
            { '+', 20 },
            { '-', 20 },
            { '*', 30 },
            { '/', 30 },
            { '^', 40 },
            { '(', 1000 },
            { '\0', 1 },
        };
        for (int i = 0; i < sizeof(r)/sizeof(PREC); ++i)
            right_prec[r[i].ch] = r[i].prec;
    }
} gPrecInit;

void infix_to_postfix(char* str, char* dest) {
    char ops[256];
    int ops_c = 0;
    do {
        int c = (unsigned char)*str;
        if (isdigit(c)) {
            *dest++=c;
        }
        else {
            int rprec = right_prec[c];
            if (rprec == 0)
                break;

            int op;
            while (ops_c > 0 && left_prec[(op = ops[ops_c-1])] >= rprec) {
                if (op != ')' && op != '(') 
                    *dest++=op;
                --ops_c;
            }
            ops[ops_c++] = c;
        }
    } while (*str++);

    *dest = 0;
}
