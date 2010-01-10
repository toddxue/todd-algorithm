/*
 * expr.h --
 *
 * expr calculation, stack based, not the yacc/bison one 
 *
 * 2010/01/10: initial release by Todd Xue
 */

#ifndef _expr_h
#define _expr_h

void infix_to_postfix(char* str, char* dest);

#endif
