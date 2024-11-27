%{
        #include <stdio.h>

        extern int yylex(void);
        
        int yyerror(const char *msg);
%}

%token ILITERAL NEWLINE OP_ABS

%%
Input   : Term Input
        | Term
        ;

Term    : Expression NEWLINE {
                printf("%d\n", $1);     
        }
        | Expression {
                printf("%d\n", $1);     
        }
        ;

Expression
        : '(' Plus ')' {
                $$ = $2;
        }
        | '(' Minus ')' {
                $$ = $2;
        }
        | '(' Multi ')' {
                $$ = $2;
        }
        | '(' Divide ')' {
                $$ = $2;
        }
        | '(' Modulo ')' {
                $$ = $2;
        }
        | '(' Abs ')' {
                $$ = $2;
        }
        | Null {
                $$ = 0;
        }
        ;

Plus    : '+' Plus_term {
                $$ = $2;
        }
        ;

Plus_term
        : Plus_term ILITERAL {
                $$ = $1 + $2;
        }
        | Plus_term Expression {
                $$ = $1 + $2;
        }
        | ILITERAL {
                $$ = $1;
        }
        | Expression {
                $$ = $1;
        }
        ;

Minus   : '-' Minus_term {
                $$ = $2;
        }
        ;

Minus_term
        : Minus_term ILITERAL {
                $$ = $1 - $2;
        }
        | Minus_term Expression {
                $$ = $1 - $2;
        }
        | ILITERAL {
                $$ = $1;
        }
        | Expression {
                $$ = $1;
        }
        ;

Multi   : '*' Multi_term {
                $$ = $2;
        }
        ;

Multi_term
        : Multi_term ILITERAL {
                $$ = $1 * $2;
        }
        | Multi_term Expression {
                $$ = $1 * $2;
        }
        | ILITERAL {
                $$ = $1;
        }
        | Expression {
                $$ = $1;
        }
        ;

Divide  : '/' Divide_term {
                $$ = $2;
        }
        ;

Divide_term
        : Divide_term ILITERAL {
                $$ = $1 / $2;
        }
        | Divide_term Expression {
                $$ = $1 / $2;
        }
        | ILITERAL {
                $$ = $1;
        }
        | Expression {
                $$ = $1;
        }
        ;

Modulo  : '%' Modulo_term {
                $$ = $2;
        }
        ;

Modulo_term
        : Modulo_term ILITERAL {
                $$ = $1 % $2;
        }
        | Modulo_term Expression {
                $$ = $1 % $2;
        }
        | ILITERAL {
                $$ = $1;
        }
        | Expression {
                $$ = $1;
        }
        ;

Abs     : OP_ABS Abs_term {
                $$ = $2 >= 0 ? $2 : -$2;
        }
        ;

Abs_term
        : ILITERAL {
                $$ = $1;
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
