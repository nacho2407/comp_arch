%{
        #include <stdio.h>

        extern int yylex();
        
        int yyerror(const char* msg);
%}
%union {
        int ival;
        char* sval;
}
%token <ival> ILITERAL OPRTR
%token <sval> SYNONYM STRING
%%
Input   : Expression
        | Expression Input
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
List    : '(' Element ')' {
                printf("L -> ( M )\n");
        }
        ;
Element : Expression Element {
                printf("M -> E M\n");
        }
        | /* ε */ {
                printf("M -> nil\n");
        }
        ;
String  : STRING {
                printf("T -> %s\n", $1);
        }
        ;
Operation
        : OPRTR Iliteral Iliteral {
                printf("O -> %c I I\n", $1);
        }
        ;
%%
int yyerror(const char* msg)
{
        fprintf(stderr, "%s\n", msg);

        return -1;
}
