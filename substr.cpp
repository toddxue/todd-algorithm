/*
 * substr.h --
 *
 * algorithms related to decide if a str is substr of another, 
 * e.g. KMP
 *
 * 2009/12/26: initial release by Todd Xue
 */

#include "substr.h"
#include <string.h>

/*
 *-------------------------------------------------------------------------
 *
 * substr --
 *      the simplest one 1st
 *
 * RETURN:
 *      NULL if not
 *      the pos of str which matches pat
 *
 *-------------------------------------------------------------------------
 */
char* substr0(int nstr, char* str, int npat, char* pat) {
    for (; nstr >= npat; --nstr, ++str) {
        if (0 == memcmp(str, pat, npat))
            return str;
    }
    return 0;
}

/*
 * KMP fail(n) function
 * it's not obvious to say it's a time-O(n) 
 * but if the value (j-i), IT'S ALWAYS INCREASING
 * see comments below
 */
void KMP_fail(int npat, char* pat, int* fail) {
    fail[0] = -1;
    int i;
    for (int j = 1; j < npat; ++j) {
        i = fail[j-1];           /*
                                  * #1
                                  * j increased, i also changed,
                                  * but i increased 1 or to -1
                                  * so j-i increased or kept same
                                  */
        while (pat[i+1] != pat[j] && i >= 0)
            i = fail[i];         /*
                                  * #2
                                  * i decreased at 1, j-i increased 
                                  */
        if (pat[i+1] != pat[j])
            fail[j] = -1;
        else 
            fail[j] = i+1;
    }
    /*
     * now j-i increased to at most (na-1-i) <= na (i = -1)
     * the initial value of j-i is 1-fail[0] = 2
     * so #2 executed at most (na-2) steps
     * so the overall is O(na), the constants depends on gcc -Ox
     */
}

char* /*KMP_substr*/substr(int na, char* a, int npat, char* pat)  {
    int* fail = new int[npat];
    KMP_fail(npat, pat, fail);
    
    // build a mask
    unsigned int mask = 0;
    for (int i = 0; i < npat; ++i) 
        mask |= 1 << (((unsigned char)pat[i]) & 31);
    
    int j = 0; 
    int v;
    int i = 0;
    while (i < na) {
#if 1
        /**
         * after add this optimization, this finally wins strstr in some cases
         * a[i..(i + (npat-1-j))] against pat[j..npat-1]
         */
        int k = i + npat-1-j;
        if (k >= na)
            break;

        if (!((1 << (((unsigned char)a[k]) & 31)) & mask)) {
            j = 0;
            i = k+1;
            continue;
        }
#endif
        
        v = a[i];
        while (v != pat[j] && j > 0) 
            j = fail[j-1]+1;

        if (v == pat[j]) {
            ++j;
            if (j == npat)
                return a + (i+1-npat);
        }
        ++i;
    }
    delete[] fail;
    return 0;
}

/*
 *-------------------------------------------------------------------------
 *
 * mystrstr --
 *      it's faster than KMP in all cases
 *
 * RETURN:
 *      NULL if not
 *      the pos of str which matches pat
 *
 *-------------------------------------------------------------------------
 */
char *mystrstr(char *str, char *pat)
{
    char *s;
    int c;

    // build a mask
    unsigned int mask = 0;
    s = pat;
    while (c = (unsigned char)*s++)
        mask |= 1 << (c & 31);

    int npat = strlen(pat);
    char* start = str;
    char* str_end = strchr(str, '\0');
    char* end = str_end - npat;

    while (str <= end) {
        /*
         * [str .. (str+npat-1)]
         */
        if (!((1 << (((unsigned char)str[npat-1]) & 31)) & mask))
            str += npat;
        else {
            char* strp = str;
            char* patp = pat;
            do {
                if (!*patp)
                    return str;
            } while (*strp++ == *patp++);
            ++str;
        }
    }
    return 0;
}

char* gstrstr(char* phaystack, char* pneedle)
{
    unsigned char *haystack, *needle;
    unsigned char b;
    unsigned char *rneedle;

    haystack = (unsigned char *) phaystack;

    if ((b = *(needle = (unsigned char *) pneedle)))
    {
        unsigned char c;
        haystack--; /* possible ANSI violation */

        {
            unsigned char a;
            do
                if (!(a = *++haystack))
                    goto ret0;
            while (a != b);
        }

        if (!(c = *++needle))
            goto foundneedle;
        ++needle;
        goto jin;

        for (;;)
        {
            {
                unsigned char a;
                if (0)
                jin:{
                        if ((a = *++haystack) == c)
                            goto crest;
                    }
                else
                    a = *++haystack;
                do
                {
                    for (; a != b; a = *++haystack)
                    {
                        if (!a)
                            goto ret0;
                        if ((a = *++haystack) == b)
                            break;
                        if (!a)
                            goto ret0;
                    }
                }
                while ((a = *++haystack) != c);
            }
        crest:
            {
                unsigned char a;
                {
                    unsigned char *rhaystack;
                    if (*(rhaystack = haystack-- + 1) == (a = *(rneedle = needle)))
                        do
                        {
                            if (!a)
                                goto foundneedle;
                            if (*++rhaystack != (a = *++needle))
                                break;
                            if (!a)
                                goto foundneedle;
                        }
                        while (*++rhaystack == (a = *++needle));
                    needle = rneedle;/* took the register-poor aproach */
                }
                if (!a)
                    break;
            }
        }
    }
foundneedle:
    return (char *) haystack;
ret0:
    return 0;
}

