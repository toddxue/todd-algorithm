/*
 * substr.h --
 *
 * algorithms related to decide if a str is substr of another, 
 * e.g. KMP
 *
 * 2009/12/26: initial release by Todd Xue
 */

#ifndef _substr_h
#define _substr_h

char const* substr(int nstr, char const* str, int npat, char const* pat);
void KMP_fail(int npat, char const* pat, int* fail);

char const *mystrstr(char const* str, char const * pat);

#endif
