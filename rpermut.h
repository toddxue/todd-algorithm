/*
 * rpermut.h --
 *
 * algorithms related to misc rpermuting
 * generate repeatable permuation
 * e.g. value set with 0,1
 * 000->100->010->110->001->101->... total 2^^m (m=sizeof(value set))
 *
 * Sun Nov 18 16:37:25 PST 2012: initial release by Todd Xue
 */

#ifndef _rpermut_h
#define _rpermut_h

#include <stddef.h>

bool rpermut_begin(size_t n, int* a, size_t m, int* vs);
bool rpermut_next (size_t n, int* a, size_t m, int* vs);

/*
 * a helper class for repeatable permuation
 * usage like
 * 
 *   Rpermut rp(n, a, m, vs);
 *   for (rp.begin(); !rp.ended; rp.next()
 *      do something for (m, vs)
 */
struct Rpermut {
    size_t n;
    int* a;
    size_t m;
    int* vs;

    bool ended;

    Rpermut(size_t n, int* a, size_t m, int* vs) : n(n), a(a), m(m), vs(vs) {}
    void begin() { ended = rpermut_begin(n, a, m, vs); }
    void next () { ended = rpermut_next(n, a, m, vs); }
};

#endif
