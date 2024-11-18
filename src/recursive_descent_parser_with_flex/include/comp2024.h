#ifndef COMP2024_H
        #define COMP2024_H

        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        typedef enum _Tag
        {
                TNIL,
                TINT,
                TSYM,
                TSTR,
                TDUO,
                TOPT
        } Tag;
        typedef struct _Pair* duo;
        typedef struct _Data
        {
                Tag tag;
                union
                {
                        int ival;
                        char* sval;
                        duo pval;
                };
        } Data;
        typedef struct _Pair
        {
                Data d[2];
        } Pair;

        Data mkint(int i);
        Data mkstr(char* s);
        Data mksym(char* s);
        Data cons(Data first, Data second);
        void writer(Data d);
        void print_list(Data d);
        void free_list(Data l);
        void error(void);

        #ifdef COMP2024_DEF
                const Data nil = { .tag = TNIL, .pval = NULL };
        #else
                extern const Data nil;
        #endif
#endif
