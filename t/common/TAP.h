#ifndef _TAP_h_
#define _TAP_h_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "xmem.h"

/**
 * OK routines to support Perl's TAP protocol
 */
inline
void _OK(bool ok, char const* hint) {
    static int global_cases;
    ++global_cases;
    if (ok)
        printf("ok %d - %s\n", global_cases, hint);
    else
        printf("not ok %d - %s\n", global_cases, hint);
    fflush(stdout);
}
#define OK(a) _OK(a, #a)

/**
 * print the summary line as `1..n' where n is
 * `grep OK $0.cpp | wc'
 */
inline
void _OK_SUM(char* prog) {
    
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "egrep '\\bOK\\\(' %s.cpp | wc -l", prog);
    FILE *f = popen(cmd, "r");
    if (f) {
        char buf[256] = {0};
        fread(buf, sizeof(buf), 1, f);
        pclose(f);
 
        char* s = buf;
        while (isspace(*s)) ++s;
        int n = strtol(s, 0, 10);
        printf("1..%d\n", n);
    }
}

#define OK_SUM() _OK_SUM(argv[0])

#endif
