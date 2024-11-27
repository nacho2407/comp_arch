#define LEX_YY_DEF
#include "lex.yy.h"

int yylex(void)
{
        return getchar();
}

void match(int c)
{
        if(LA == c)
                LA = yylex();
        else
                error();
}

void match_condition(int begin, int end)
{
        if(begin <= LA && LA <= end)
                LA = yylex();
        else
                error();
}
