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
    bool exprs_for_24(int a1, int a2, int a3, int a4)
    {
        int ar[4] = {a1, a2, a3, a4};
        sort_quick(4, ar);
        
        int opr[3];
        Rpermut rp(sizeof(ops)/sizeof(int), ops, 3, opr);

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

                bool div_zero = false;
                if (24 == op_eval(op1, a, op_eval(op2, b, op_eval(op3, c, d, &div_zero), &div_zero), &div_zero) && div_zero == false) {
                    fprintf(stdout, "%d %s (%d %s (%d %s %d))\n", a, op_strs[op1], b, op_strs[op2], c, op_strs[op3], d);
                    found = true;
                }

                if (24 == op_eval(op2, op_eval(op1, a, b, &div_zero), op_eval(op3, c, d, &div_zero), &div_zero) && div_zero == false) {
                    fprintf(stdout, "(%d %s %d) %s (%d %s %d)\n", a, op_strs[op1], b, op_strs[op2], c, op_strs[op3], d);
                    found = true;
                }
            }
        }

        return found;
    }
}
