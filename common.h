#ifndef _common_h
#define _common_h

#include <stddef.h>

template <size_t n> inline int alen(int (&a)[n]) { return static_cast<int>(n); }

template <typename T> struct mem_guard {
    T* p;
    mem_guard(T* p) : p(p) {} 
    ~mem_guard() { delete p; }
};
#define MEM_GUARD(T, p) mem_guard<T> MEM_GUARD_ ## _p(p);

template <typename T> struct arrmem_guard {
    T* p;
    arrmem_guard(T* p) : p(p) {}
    ~arrmem_guard() { delete[] p; }
};
#define ARRMEM_GUARD(T, p) arrmem_guard<T> ARRMEM_GUARD_##_p(p);

inline void reverse(int n, int* b) { for (int* e = b + n - 1; b < e; ++b, --e) { int tmp = *b; *b = *e; *e = tmp; } }

#endif
