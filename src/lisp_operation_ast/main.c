#include "ast.h"
#include "y.tab.h"

int main(void)
{
        func_stk = (char**) calloc(MAX_STK, sizeof(char*));
        sp = 0;
        
        yyparse();

        free(func_stk);

        return 0;
}
