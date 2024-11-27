#define Y_TAB_DEF
#include "y.tab.h"

int yyparse(void)
{
        Data data = nil;

        for(int lex = yylex(); lex; lex = yylex()) {
                token(lex, &data);

                writer(data);
                printf("\n");

                if(data.tag == TDUO)
                        free_list(data);
        }

        return 0;
}

void token(int lex, Data* data)
{
        switch(lex) {
                case ILITERAL:
                        *data = mkint(atoi(yytext));

                        break;
                case SYNONYM:
                        *data = mksym(yytext);

                        break;
                case LIST_B:
                        *data = list();

                        break;
                case STRING:
                        *data = mkstr(yytext);

                        break;
                case OPRTR:
                        opt_stk[op++] = yytext[0];

                        calc();
                        calc();

                        int second = int_stk[--ip];
                        int first = int_stk[--ip];

                        switch(opt_stk[--op]) {
                                case '+':
                                        int_stk[ip++] = first + second;

                                        break;
                                case '-':
                                        int_stk[ip++] = first - second;

                                        break;
                                case '*':
                                        int_stk[ip++] = first * second;

                                        break;
                                case '/':
                                        int_stk[ip++] = first / second;

                                        break;
                        }

                        *data = mkint(int_stk[--ip]);

                        break;
                case SIMPLE_ARITH:
                        *data = mkint(oprtr_val);

                        break;
                default:
                        error();
        }
}

Data list(void)
{
        Data first = nil;

        int lex = yylex();

        if(lex == LIST_E)
                return nil;
        else
                token(lex, &first);
        
        return cons(first, list());
}

void calc(void)
{
        int lex = yylex();

        switch(lex) {
                case ILITERAL:
                        int_stk[ip++] = atoi(yytext);

                        break;
                case LIST_B:
                        int_stk[ip++] = list().pval->d[0].ival;

                        break;
                case OPRTR:
                        opt_stk[op++] = yytext[0];

                        calc();
                        calc();

                        int second = int_stk[--ip];
                        int first = int_stk[--ip];

                        switch(opt_stk[--op]) {
                                case '+':
                                        int_stk[ip++] = first + second;

                                        break;
                                case '-':
                                        int_stk[ip++] = first - second;

                                        break;
                                case '*':
                                        int_stk[ip++] = first * second;

                                        break;
                                case '/':
                                        int_stk[ip++] = first / second;

                                        break;
                        }
                        break;
                default:
                        error();
        }
}
