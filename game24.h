/*
 * game24.h --
 *
 * algorithms related to the calculation of the game24
 *
 * Fri, Dec 14, 2012  2:35:20 PM: initial release by Todd Xue
 */

#ifndef _game24_h
#define _game24_h

namespace game24 {
    /**
     * it turns out not a trivial task after go through 1st look and ...
     * there a lot ways to do this, the current way is like
     * 
     * we've operator +, -, -r, *, /, /r
     * 
     * +: (a, b) -> a+b
     * *: (a, b) -> a*b
     * -: (a, b) -> a-b
     * -r: (a,b) -> b-a
     * /: (a, b) -> a/b
     * /r: (a,b) -> b/a
     *
     * the purpose of invent -r, /r is to make the order of (a,b) not imporant
     * in our algorithm
     *
     *
     * the next steps are basically we only have 2 forms of expression:
     *
     *  a ? (b ? (c ? d)) 
     *  (a ? b) ? (c ? d)
     *  
     * where ? is one of above 6 operators 

     * Algorithm:
     * 
     *  for (a,b,c,d) in all permutation of 4 numbers input 
     *     for (op1, op2, op3) in all repeatable triple permutation of + - -r * / /r
     *        if (24 == a op1 (b op2 (c op3 d)))
     *            output "a op1 (b op2 (c op3 d))"
     *        if (24 == (a op1 b) op2 (c op3 d))
     *            output "(a op1 b) op2 (c op3 d)"
     */
    
    enum Op {
        op_add  = 0,
        op_sub  = 1,
        op_subr = 2,
        op_mul  = 3, 
        op_div  = 4,
        op_divr = 5,
        op_max  = 6,
    };
    
    static int ops[op_max] = { op_add, op_sub, op_subr, op_mul, op_div, op_divr };
    static char const* op_strs[op_max] = { "+", "-", "-r", "x", "/", "/r" };

    inline
    int op_eval(int op, int a, int b, bool* div_zero) {
        switch (op) {
        case op_add:  return a + b;
        case op_sub:  return a - b;
        case op_subr: return b - a;
        case op_mul:  return a + b;

        case op_div:  
            if (b == 0) {
                *div_zero = true;
                return 0;
            }
            else 
                return a / b;

        case op_divr: 
            if (a == 0) {
                *div_zero = true;
                return 0;
            }
            else 
                return b / a;

        default:
            throw "bad things happened";
        }
        return 0; /** never reach here **/
    }

    bool exprs_for_24(int a1, int a2, int a3, int a4);
}

#endif
