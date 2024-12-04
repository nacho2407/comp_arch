%{
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "y.tab.h"

static int sval_active = 0;
%}

iliteral        [+-]?[0-9]+
list_begin      \(
list_end        \)
whitespace      [ \t]+
newline         \n
comment         ;.*\n
operator        [\+\-\*\/]
func_abs        abs
func_setq       setq
func_print      print
synonym         [_A-Za-z][_A-Za-z0-9]*
end             \0
else            .

%%

{iliteral} {
        if(sval_active) {
                free(yylval.sval);
                sval_active = 0;
        }

        yylval.ival = atoi(yytext);

        return ILITERAL;
}

{list_begin} {
        return '(';
}

{list_end} {
        return ')';
}

{whitespace} {
        /* do nothing */
}

{newline} {
        return NEWLINE;
}

{comment} {
        /* do nothing */
}

{operator} {
        func_stk[sp++] = strdup(yytext);

        return OPERATOR;
}

{func_abs} {
        func_stk[sp++] = strdup(yytext);

        return FUNC_ABS;
}

{func_setq} {
        func_stk[sp++] = strdup(yytext);
        
        return FUNC_SETQ;
}

{func_print} {
        func_stk[sp++] = strdup(yytext);
        
        return FUNC_PRINT;
}

{synonym} {
        if(sval_active) {
                free(yylval.sval);
                sval_active = 0;
        }

        yylval.sval = strdup(yytext);

        return SYNONYM;
}

{end} {
        return 0;
}

{else} {
        /* do nothing */
}

%%

int yywrap()
{
        return 1;
}
