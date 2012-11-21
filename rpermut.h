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

bool rpermut_begin(int n, int* a, int m, int* vs);
bool rpermut_next (int n, int* a, int m, int* vs);

#endif
