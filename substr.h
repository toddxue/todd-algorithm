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

char* substr(int nstr, char* str, int npat, char* pat);
void KMP_fail(int npat, char* pat, int* fail);

char *mystrstr(char *str, char *pat);

#endif
