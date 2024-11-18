#define COMP2024_DEF
#include "comp2024.h"

Data mkint(int i)
{
        Data d = { TINT, .ival = i };

        return d;
}

Data mksym(char* s)
{
        Data d = { TSYM, .sval = (char*) malloc(strlen(s) + 1 * sizeof(char)) };

        strcpy(d.sval, s);

        return d;
}

Data mkstr(char* s)
{
        Data d = mksym(s);

        d.tag = TSTR;

        return d;
}

Data cons(Data a, Data b)
{
        Pair* pair = (Pair*) malloc(sizeof(Pair));
        pair->d[0] = a;
        pair->d[1] = b;

        Data d = { TDUO, .pval = pair };

        return d;
}

void writer(Data d)
{
        switch(d.tag) {
                case TINT:
                        printf("(INT, %d)", d.ival);
                        
                        break;
                case TSYM:
                        printf("(SYM, %s)", d.sval);

                        free(d.sval);

                        break;
                case TSTR:
                        printf("(STR, %s)", d.sval);

                        free(d.sval);

                        break;
                case TNIL:
                        printf("NIL");

                        break;
                case TDUO:
                        print_list(d);

                        break;
        }
}

void print_list(Data d)
{
        printf("(");
        
        writer(d.pval->d[0]);

        printf(" . ");

        writer(d.pval->d[1]);

        printf(")");
}

void free_list(Data l)
{
        if(l.tag != TDUO)
                return;
        
        free_list(l.pval->d[1]);

        free(l.pval);
}

void error(void)
{
        fprintf(stderr, "syntax error\n");

        exit(1);
}
