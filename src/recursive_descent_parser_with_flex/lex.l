%{
#define LEX_YY_DEF
#include "lex.yy.h"
%}
iliteral        [+-]?[0-9]+
synonym  [a-zA-Z][a-zA-Z0-9]*
list_begin      \(
list_end        \)
whitespace      [ \t\n]+
comment ;.*\n
string  \".*\"
operator        [\+\-\/\*]
end     \0
else    .
%%
{iliteral} {
        return ILITERAL;
}
{synonym} {
        return SYNONYM;
}
{list_begin} {
        return LIST_B;
}
{list_end} {
        return LIST_E;
}
{whitespace} {
        /* do nothing */
}
{comment} {
        /* do nothing */
}
{string} {
        return STRING;
}
{operator} {
        return OPRTR;
}
{operator}[ \t]+{iliteral}[ \t]+{iliteral} {
        int i = 0;

        char operator = yytext[i];

        char buf[MAX_BUF] = { 0 };

        i += 2;
        for(; isdigit(yytext[i]); i++)
                buf[i - 2] = yytext[i];
        buf[i] = '\0';

        int first = atoi(buf);

        int j = ++i;
        for(; isdigit(yytext[i]); i++)
                buf[i - j] = yytext[i];
        buf[j] = '\0';

        int second = atoi(buf);

        switch(operator) {
                case '+':
                        oprtr_val = first + second;

                        break;
                case '-':
                        oprtr_val = first - second;

                        break;
                case '*':
                        oprtr_val = first * second;

                        break;
                case '/':
                        oprtr_val = first / second;

                        break;
        }

        return SIMPLE_ARITH;
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
