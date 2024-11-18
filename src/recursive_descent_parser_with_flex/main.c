#include "comp2024.h"
#include "lex.yy.h"

#define MAX_STK 128

extern int yylex(void);

static void yyparse(void);

static void token(int lex, Data* data);
static Data list(void);
static void calc(void);

extern char* yytext;

static int int_stk[MAX_STK];
static int ip = 0;

static char opt_stk[MAX_STK];
static int op = 0;

int main(void)
{
        yyparse();

        return 0;
}

/*
        - EBNF
        
        <token> ::= <iliteral>
                  | <synonym>
                  | <list_begin>
                  | <list_end>
                  | <whitespace>
                  | <comment>
                  | <string>
                  | <operator>
                  ;

        <iliteral> ::= [ '+' | '-' ] <digit> { <digit> } ;
        <digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' ;

        <synonym> ::= <alphabet> { <alphabet> | <digit> } ;
        <alphabet> ::= 'a' | ... | 'z' | 'A' | ... | 'Z' ;

        <list_begin> ::= '(' ;
        <list_end> ::= ')' ;

        <whitespace> ::= ' ' | '\t' | '\n' ;

        <comment> ::= ';' { <character> } '\n' ;

        <string> ::= '"' { <character> } '"' ;

        <character> ::= (any valid ASCII) ;

        <operator> ::= '+' | '-' | '/' | '*' ;
*/

static void yyparse(void)
{
        Data data = nil;

        for(int lex = yylex(); lex; lex = yylex()) {
                token(lex, &data);

                writer(data);
                printf("\n");

                if(data.tag == TDUO)
                        free_list(data);
        }
}

static void token(int lex, Data* data)
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

static Data list(void)
{
        Data first = nil;

        int lex = yylex();

        if(lex == LIST_E)
                return nil;
        else
                token(lex, &first);
        
        return cons(first, list());
}

static void calc(void)
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
