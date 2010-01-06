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
 * substr1 --
 *      the simplest one
 *
 * RETURN:
 *      NULL if not
 *      the pos of str which matches pat
 *
 *-------------------------------------------------------------------------
 */
char* substr(int nstr, char* str, int npat, char* pat) {
    for (; nstr >= npat; --nstr, ++str) {
        if (0 == memcmp(str, pat, npat))
            return str;
    }
    return 0;
}
