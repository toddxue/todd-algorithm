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
     * we've operator +, -, *, /
     * 
     * +: (a, b) -> a+b
     * *: (a, b) -> a*b
     * -: (a, b) -> a-b
     * -r: (a,b) -> b-a
     *
     * the next steps are basically we only have 5 forms of expression:
     *
     *  form1: ((a ? b) ? c) ? d) 
     *  form2: (a ? (b ? c)) ? d) 
     *  form3: (a ? b) ? (c ? d)
     *  form4: a ? ((b ? c) ? d)) 
     *  form5: a ? (b ? (c ? d)) 
     *  
     * where ? is one of above 6 operators 

     * Algorithm:
     * 
     *  for (a,b,c,d) in all permutation of 4 numbers input 
     *     for (op1, op2, op3) in all repeatable triple permutation of + - -r * / /r
     *        for form in {form1,...,form5}
     *          if evaluate(form) is 24
     *            print form
     */
    bool exprs_for_24(int a1, int a2, int a3, int a4);
}

#endif
