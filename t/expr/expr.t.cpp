#include "TAP.h"
#include "expr.h"
#include <string.h>

int main(int argc, char* argv[]) {
    OK_SUM();
    
    {
        char e[] = "1+2";
        char dest[sizeof(e)];
        infix_to_postfix(e, dest);
        OK(0 == strcmp(dest, "12+"));
    }

    {
        char e[] = "1+2*3";
        char dest[sizeof(e)];
        infix_to_postfix(e, dest);
        OK(0 == strcmp(dest, "123*+"));
    }

    {
        char e[] = "(1+2)*3";
        char dest[sizeof(e)];
        infix_to_postfix(e, dest);
        OK(0 == strcmp(dest, "12+3*"));
    }
    return 0;
}
