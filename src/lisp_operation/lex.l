%{
#include "y.tab.h"
%}

iliteral        [+-]?[0-9]+
list_begin      \(
list_end        \)
whitespace      [ \t]+
newline         \n
comment         ;.*\n
operator        [\+\-\/\*\%]
op_abs          abs
end             \0
else            .

%%

{iliteral} {
        yylval = atoi(yytext);

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
        return yytext[0];
}

{op_abs} {
        return OP_ABS;
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
