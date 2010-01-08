#include "TAP.h"
#include "substr.h"
#include <string.h>

int KMP_fail_stupid(int npat, char* pat, int* fail) {
    fail[0] = -1;
    for (int i = 1; i < npat; ++i) {
        int j = i-1;
        fail[i] = -1;
        for (; j>= 0; --j) {
            // [0~j] vesus [i-j,i]
            bool eq = true;
            for (int k = 0; k <= j; ++k)
                if (pat[k] != pat[i-j+k]) {
                    eq = false;
                    break;
                }
            if (eq) {
                fail[i] = j;
                break;
            }
        }
    }
}

bool rcheck(int npat) {
    char* pat = new char[npat];
    int* fail1 = new int[npat];
    int* fail2 = new int[npat];
    int r = true;
    for (int bound = 10; bound > 0; --bound) {
        for (int i = 0; i < npat; ++i) 
            pat[i] = random() % bound;

        KMP_fail_stupid(npat, pat, fail1);
        KMP_fail       (npat, pat, fail2);
        if (0 != memcmp(fail1, fail2, sizeof(int) * npat)) {
            r = false;
            break;
        }
    }
    delete[] fail1;
    delete[] fail2;
    return r;
}

int main(int argc, char* argv[]) {

    OK_SUM();
    
    {
        char pat[1] = {1};
        int fail[1];
        KMP_fail(1, pat, fail);
        OK(fail[0] == -1);
        KMP_fail_stupid(1, pat, fail);
        OK(fail[0] == -1);
    }

    {
        char pat[2] = {1,1};
        int fail[2];
        KMP_fail(2, pat, fail);
        OK(fail[0] == -1 && fail[1] == 0);
        KMP_fail_stupid(2, pat, fail);
        OK(fail[0] == -1 && fail[1] == 0);
    }

    {
        char pat[3] = {1,2,1};
        int fail[3];
        KMP_fail(3, pat, fail);
        OK(fail[0] == -1 && fail[1] == -1 && fail[2] == 0);
        KMP_fail_stupid(3, pat, fail);
        OK(fail[0] == -1 && fail[1] == -1 && fail[2] == 0);
    }

    {
        char pat[4] = {1,2,1,2};
        int fail[4];
        KMP_fail(4, pat, fail);
        OK(fail[0] == -1 && fail[1] == -1 && fail[2] == 0 && fail[3] == 1);
        KMP_fail_stupid(4, pat, fail);
        OK(fail[0] == -1 && fail[1] == -1 && fail[2] == 0 && fail[3] == 1);
    }

    OK(rcheck(1));
    OK(rcheck(2));
    OK(rcheck(2));
    OK(rcheck(4));
    OK(rcheck(5));
    OK(rcheck(6));
    OK(rcheck(7));
    OK(rcheck(8));
    OK(rcheck(10));
    OK(rcheck(20));
    OK(rcheck(40));
    OK(rcheck(80));
    OK(rcheck(100));
    OK(rcheck(200));
    OK(rcheck(1000));
    return 0;
}
