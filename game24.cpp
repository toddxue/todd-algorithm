#include "game24.h"
#include "sort.h"
#include <algorithm>
#include "rpermut.h"

namespace game24 {
    /*
     * Algorithm:
     * 
     *  for (a,b,c,d) in all permutation of 4 numbers input 
     *     for (op1, op2, op3) in all repeatable triple permutation of + - -r * / /r
     *        if (24 == a op1 (b op2 (c op3 d)))
     *            output "a op1 (b op2 (c op3 d))"
     *        if (24 == (a op1 b) op2 (c op3 d))
     *            output "(a op1 b) op2 (c op3 d)"
     */

    inline
    bool swapable(int op) { return op == '*' || op == '+'; }
    
    inline
    bool eq(double a, double b) { return (a-b) * (a-b) < 0.01; }

    inline
    double eval(int op, double a, double b, bool* div_zero) {
        switch (op) {
        case '+':  return a + b;
        case '-':  return a - b;
        case '*':  return a * b;
        case '/':  
            if (b == 0) {
                *div_zero = true;
                return 0;
            }
            else 
                return a / b;
        default:
            throw "bad things happened";
        }
        return 0; /** never reach here **/
    }

    inline
    bool form1(int a, int b, int c, int d, int op1, int op2, int op3) {
        // ((a op1 b) op2 c) op3 d
        if (a > b && swapable(op1))
            return false;

        bool div_zero = false;
        double r = eval(op3, eval(op2, eval(op1, a, b, &div_zero), c, &div_zero), d, &div_zero);
        if (!div_zero && eq(r, 24)) {
            fprintf(stdout, "((%d %c %d) %c %d) %c %d\n", a, char(op1), b, char(op2), c, char(op3), d);
            return true;
        }
        return false;
    }

    inline
    bool form2(int a, int b, int c, int d, int op1, int op2, int op3) {
        // (a op1 (b op2 c)) op3 d
        if (b > c && swapable(op2))
            return false;

        // already covered by form2 in this case
        if (swapable(op1))
            return false;

        bool div_zero = false;
        double r = eval(op3, eval(op1, a, eval(op2, b, c, &div_zero), &div_zero), d, &div_zero);
        if (!div_zero && eq(r, 24)) {
            fprintf(stdout, "(%d %c (%d %c %d)) %c %d\n", a, char(op1), b, char(op2), c, char(op3), d);
            return true;
        }
        return false;
    }


    inline
    bool form3(int a, int b, int c, int d, int op1, int op2, int op3) {
        // (a op1 b) op2 (c op3 d)
        if (a > b && swapable(op1))
            return false;

        if (c > d && swapable(op3))
            return false;

        bool div_zero = false;
        double r = eval(op2, eval(op1, a, b, &div_zero), eval(op3, c, d, &div_zero), &div_zero);
        if (!div_zero && eq(r, 24)) {
            fprintf(stdout, "(%d %c %d) %c (%d %c %d)\n", a, char(op1), b, char(op2), c, char(op3), d);
            return true;
        }
        return false;
    }

    inline
    bool form4(int a, int b, int c, int d, int op1, int op2, int op3) {
        // a op1 ((b op2 c) op3 d)
        if (b > c && swapable(op2))
            return false;

        // already covered by form1 in this case
        if (swapable(op1))
            return false;

        bool div_zero = false;
        double r = eval(op1, a, eval(op3, eval(op2, b, c, &div_zero), d, &div_zero), &div_zero);
        if (!div_zero && eq(r, 24)) {
            fprintf(stdout, "%d %c ((%d %c %d) %c %d)\n", a, char(op1), b, char(op2), c, char(op3), d);
            return true;
        }
        return false;
    }

    inline
    bool form5(int a, int b, int c, int d, int op1, int op2, int op3) {
        // a op1 (b op2 (c op3 d))
        if (c > d && swapable(op3))
            return false;

        // already covered by form1 in this case
        if (swapable(op1))
            return false;

        // already covered by form4 in this case
        if (swapable(op2))
            return false;

        bool div_zero = false;
        double r = eval(op1, a, eval(op2, b, eval(op3, c, d, &div_zero), &div_zero), &div_zero);
        if (!div_zero && eq(r, 24)) {
            fprintf(stdout, "%d %c (%d %c (%d %c %d))\n", a, char(op1), b, char(op2), c, char(op3), d);
            return true;
        }
        return false;
    }

    
    bool exprs_for_24(int a1, int a2, int a3, int a4)
    {
        int ar[4] = {a1, a2, a3, a4};
        sort_quick(4, ar);

        int ops[4] = {'+', '-', '*', '/'}; 
        int opr[3];
        Rpermut rp(3, opr, sizeof(ops)/sizeof(int), ops);

        int a, b, c, d;
        int op1, op2, op3;
        
        bool found = false;

        for (; std::next_permutation(ar, ar+4); ) {
            
            a = ar[0];
            b = ar[1];
            c = ar[2];
            d = ar[3];

            for (rp.begin(); !rp.ended; rp.next()) {
                op1 = opr[0];
                op2 = opr[1];
                op3 = opr[2];

                if (form1(a, b, c, d, op1, op2, op3) ||
                    form2(a, b, c, d, op1, op2, op3) ||
                    form3(a, b, c, d, op1, op2, op3) ||
                    form4(a, b, c, d, op1, op2, op3) ||
                    form5(a, b, c, d, op1, op2, op3))
                    found = true;
            }
        }

        return found;
    }
}
