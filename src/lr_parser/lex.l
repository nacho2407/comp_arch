%{
#include <stdlib.h>
#include <string.h>

#include "y.tab.h"

static int sval_active = 0;
%}

iliteral        [+-]?[0-9]+
synonym         [_A-Za-z][_A-Za-z0-9]*
list_begin      \(
list_end        \)
whitespace      [ \t\n]+
comment         ;.*\n
string          \".*\"
operator        [\+\-\/\*]
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

{synonym} {
        if(sval_active) {
                free(yylval.sval);
                sval_active = 0;
        }

        yylval.sval = strdup(yytext);
        sval_active = 1;

        return SYNONYM;
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

{comment} {
        /* do nothing */
}

{string} {
        if(sval_active) {
                free(yylval.sval);
                sval_active = 0;
        }

        yylval.sval = strdup(yytext);
        sval_active = 1;

        return STRING;
}

{operator} {
        if(sval_active) {
                free(yylval.sval);
                sval_active = 0;
        }

        yylval.ival = yytext[0];

        return OPRTR;
}

{end} {
        if(sval_active) {
                free(yylval.sval);
                sval_active = 0;
        }
        
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
