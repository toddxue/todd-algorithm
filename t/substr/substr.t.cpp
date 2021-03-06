#include "TAP.h"
#include "substr.h"
#include <string.h>

bool rcheck(int nstr, int npat, int c) {
    
    char* pat = new char[npat+1];
    char* str = new char[nstr+1];
    
    for (; c>0; --c) {
        for (int i = 0; i < nstr; ++i)
            str[i] = 'a' + random() % 5;
        str[nstr] = 0;

        for (int i = 0; i < npat; ++i)
            pat[i] = 'a' + random() % 5;
        pat[npat] = 0;

        char const* r1 = mystrstr(str, pat);
        char const* r2 = substr(nstr, str, npat, pat);
    
        if (r1 != r2)
            return false;
    }
    delete[] str;
    delete[] pat;
    return true;
}

int main(int argc, char* argv[]) {
    OK_SUM();

    char const* s = "abc";

    OK(0 == substr(3, "abc", 1, "d"));
    OK(s == substr(3, "abc", 1, "a"));
    OK(s+1 == substr(3, "abc", 1, "b"));
    OK(s+1 == substr(3, "abc", 1, "bc"));

    OK(rcheck(10, 1, 100));
    OK(rcheck(10, 2, 100));
    OK(rcheck(10, 3, 100));
    OK(rcheck(20, 3, 100));
    OK(rcheck(20, 4, 100));
    OK(rcheck(20, 5, 100));
    OK(rcheck(20, 6, 100));
    OK(rcheck(20, 7, 100));
    OK(rcheck(20, 8, 100));

    OK(rcheck(30, 3, 100));
    OK(rcheck(30, 4, 100));
    OK(rcheck(30, 5, 100));
    OK(rcheck(30, 6, 100));
    OK(rcheck(30, 7, 100));
    OK(rcheck(30, 8, 100));

    OK(rcheck(100, 8, 100));
    OK(rcheck(1000, 8, 100));
    OK(rcheck(10000, 8, 100));
    return 0;
}
