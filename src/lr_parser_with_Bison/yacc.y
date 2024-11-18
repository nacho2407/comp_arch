%{
        #include <stdio.h>

        extern int yylex();
        
        int yyerror(char *s);
%}
%union {
        int ival;
        char* sval;
}
%token <ival> ILITERAL
%token <sval> SYNONYM STRING OPRTR
%token NEXT
%%
Input   : Expression NEXT {
                return yyparse();
        }
        | /* ε */ {
                /* do nothing */
        }
        ;
Expression
        : Iliteral {
                printf("E -> I\n");
        }
        | Synonym {
                printf("E -> S\n");
        }
        | List {
                printf("E -> L\n");
        }
        | String {
                printf("E -> T\n");
        }
        | Operation {
                printf("E -> O\n");
        }
        ;
Iliteral
        : ILITERAL {
                printf("I -> %d\n", $1);
        }
        ;
Synonym : SYNONYM {
                printf("S -> %s\n", $1);
        }
        ;
List    : '(' Nullable_Expression ')' {
                printf("L -> ( N )\n");
        }
        ;
Nullable_Expression
        : Expression Nullable_Expression {
                printf("N -> E N\n");
        }
        | /* ε */ {
                printf("N -> nil\n");
        }
        ;
String  : STRING {
                printf("T -> %s\n", $1);
        }
        ;
Operation
        : Operator Iliteral Iliteral {
                printf("O -> P I I\n");
        }
        ;
Operator
        : OPRTR {
                printf("P -> %s\n", $1);
        }
        ;
%%
int yyerror(char* s)
{
        fprintf(stderr, "%s\n", s);

        return -1;
}
