#include "comp2024.h"

#define MAX_BUF 128

static void yyparse(void);
static int yylex(void);
static void match(int c);
static void match_condition(int begin, int end);
static Data token(void);
static void whitespace(void);
static Data integer(void);
static void non_zero(void);
static void digit(void);
static Data synonym(void);
static void non_digit(void);
static void alphabet(void);
static Data list(void);

static int LA; /* Lookahead global variable */

static char* buf;
static int bufp = 0;

int main(void)
{
        yyparse();

        return 0;
}

/*
        - EBNF
        
        <token> ::= { <whitespace> } ( <integer> | <synonym> | <list> | <nil> ) ;

        <whitespace> ::= ' ' | '\t' | '\n' ;
        
        <integer> ::= '0' | <non_zero> { <digit> } ;
        <non_zero> ::= '1' | '2' | '3'
                     | '4' | '5' | '6'
                     | '7' | '8' | '9'
                     ;
        <digit> ::= <non_zero> | '0' ;

        <synonym> ::= <non_digit> { <non_digit> | <digit> } ;
        <non_digit> ::= <alphabet> | '_' ;
        <alphabet> ::= ... ;

        <list_begin> ::= '(' ;
        <list_end> ::= ')' ;

        <nil> ::= <list_begin> { <whitespace> } <list_end> ;
*/

static void yyparse(void)
{
        Data d;

        buf = (char*) calloc(MAX_BUF, sizeof(char));

        LA = yylex();

        whitespace();
        while(LA != EOF) {
                d = token();

                writer(d);
                printf("\n");

                if(d.tag == TDUO)
                        free_list(d);

                whitespace();
        }

        free(buf);
        buf = NULL;
}

static int yylex(void)
{
        return getchar();
}

static void match(int c)
{
        if(LA == c)
                LA = yylex();
        else
                error();
}

static void match_condition(int begin, int end)
{
        if(begin <= LA && LA <= end)
                LA = yylex();
        else
                error();
}

static Data token(void)
{
        Data d;
        
        if('0' <= LA && LA <= '9')
                d = integer();
        else if(('a' <= LA && LA <= 'z') || ('A' <= LA && LA <= 'Z') || LA == '_')
                d = synonym();
        else if(LA == '(') {
                match('(');

                d = list();
        } else
                error();

        return d;
}

static void whitespace(void)
{
        while(LA == ' ' || LA == '\t' || LA == '\n')
                match(LA);
}

static Data integer(void)
{
        Data d;

        if(LA == '0') {
                match('0');

                d = mkint(0);
        } else {
                buf[bufp++] = (char) LA;
                non_zero();

                while('0' <= LA && LA <= '9') {
                        buf[bufp++] = (char) LA;
                        digit();
                }
                buf[bufp] = '\0';
                
                d = mkint(atoi(buf));
                bufp = 0;
        }

        return d;
}

static void non_zero(void)
{
        match_condition('1', '9');
}

static void digit(void)
{
        if(LA == '0')
                match('0');
        else
                non_zero();
}

static Data synonym(void)
{
        Data d;

        buf[bufp++] = (char) LA;
        non_digit();

        while(('0' <= LA && LA <= '9') || ('a' <= LA && LA <= 'z') ||
              ('A' <= LA && LA <= 'Z') || LA == '_') {
                if('0' <= LA && LA <= '9') {
                        buf[bufp++] = (char) LA;

                        digit();
                } else {
                        buf[bufp++] = (char) LA;

                        non_digit();
                }
        }
        buf[bufp] = '\0';

        d = mksym(buf);
        bufp = 0;

        return d;
}

static void non_digit(void)
{
        if(LA == '_')
                match('_');
        else
                alphabet();
}

static void alphabet(void)
{
        if('a' <= LA && LA <= 'z')
                match_condition('a', 'z');
        else
                match_condition('A', 'Z');
}

static Data list(void)
{
        whitespace();

        if(LA == ')') {
                match(')');

                return nil;
        }

        Data first = nil;

        first = token();

        return cons(first, list());
}
