#define Y_TAB_DEF
#include "y.tab.h"

int yyparse(void)
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

        return 0;
}

Data token(void)
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

void whitespace(void)
{
        while(LA == ' ' || LA == '\t' || LA == '\n')
                match(LA);
}

Data integer(void)
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

void non_zero(void)
{
        match_condition('1', '9');
}

void digit(void)
{
        if(LA == '0')
                match('0');
        else
                non_zero();
}

Data synonym(void)
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

void non_digit(void)
{
        if(LA == '_')
                match('_');
        else
                alphabet();
}

void alphabet(void)
{
        if('a' <= LA && LA <= 'z')
                match_condition('a', 'z');
        else
                match_condition('A', 'Z');
}

Data list(void)
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
