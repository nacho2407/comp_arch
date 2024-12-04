%{
#include <stddef.h>

#include "ast.h"

extern int yylex(void);

int yyerror(const char *msg);
%}

%union {
        int ival;
        char* sval;
        node pval;
}

%token <ival> ILITERAL
%token <sval> SYNONYM
%token NEWLINE OPERATOR FUNC_ABS FUNC_SETQ FUNC_PRINT

%type <pval> Expression Operation Operation_term Abs Abs_term Setq Setq_term Print Print_term

%%

Input   : Term Input
        | Term
        ;

Term    : Expression NEWLINE {
                print_tree($1, 0);

                free_node($1);

                $1 = NULL;
        }
        | Expression {
                print_tree($1, 0);

                free_node($1);

                $1 = NULL;    
        }
        ;

Expression
        : '(' Operation ')' {
                free(func_stk[--sp]);

                $$ = $2;
        }
        | '(' Abs ')' {
                free(func_stk[--sp]);
                
                $$ = $2;
        }
        | '(' Setq ')' {
                free(func_stk[--sp]);
                
                $$ = $2;
        }
        | '(' Print ')' {
                free(func_stk[--sp]);
                
                $$ = $2;
        }
        | Null {
                $$ = &nil;
        }
        ;

Operation
        : OPERATOR Operation_term {
                $$ = $2;
        }
        ;

Operation_term
        : Operation_term ILITERAL {
                $$ = mk_func_node(func_stk[sp - 1], $1, mk_int_node($2));
        }
        | Operation_term SYNONYM {
                $$ = mk_func_node(func_stk[sp - 1], $1, mk_sym_node($2));
        }
        | Operation_term Expression {
                $$ = mk_func_node(func_stk[sp - 1], $1, $2);
        }
        | ILITERAL {
                $$ = mk_int_node($1);
        }
        | SYNONYM {
                $$ = mk_sym_node($1);
        }
        | Expression {
                $$ = $1;
        }
        ;

Abs     : FUNC_ABS Abs_term {
                $$ = mk_func_node(func_stk[sp - 1], $2, &nil);
        }
        ;

Abs_term
        : ILITERAL {
                $$ = mk_int_node($1);
        }
        | SYNONYM {
                $$ = mk_sym_node($1);
        }
        | Expression {
                $$ = $1;
        }
        ;

Setq    : FUNC_SETQ SYNONYM Setq_term {
                $$ = mk_func_node(func_stk[sp - 1], mk_sym_node($2), $3);
        }
        ;

Setq_term
        : ILITERAL {
                $$ = mk_int_node($1);
        }
        | SYNONYM {
                $$ = mk_sym_node($1);
        }
        | Expression {
                $$ = $1;
        }
        ;

Print   : FUNC_PRINT Print_term {
                $$ = mk_func_node(func_stk[sp - 1], $2, &nil);
        }
        ;

Print_term
        : ILITERAL {
                $$ = mk_int_node($1);
        }
        | SYNONYM {
                $$ = mk_sym_node($1);
        }
        | Expression {
                $$ = $1;
        }
        ;

Null    : '(' ')' ;

%%

int yyerror(const char* msg)
{
        fprintf(stderr, "%s\n", msg);

        return -1;
}
