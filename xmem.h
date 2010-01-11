/*
 * xmem.h --
 *
 *     cygwin hardness:
 *     ref to http://www.cygwin.com/faq.html 6.34
 * 
 *     so change a `x' prefix to avoid this issue, ALSO
 *     this brings a benifits:
 *          
 *         routines malloc/free doesn't affect the mem stat
 *         but this will let us avoid using routines such as strdup
 * 
 * 2010/01/11: initial release by Todd Xue
 */

#ifndef _xmem_h
#define _xmem_h

void* xmalloc(size_t size) ;
void xfree(void* ptr);
void* xcalloc(size_t size, int elem_size);

#endif
