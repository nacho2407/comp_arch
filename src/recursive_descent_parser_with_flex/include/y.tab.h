#ifndef Y_TAB_H
        #define Y_TAB_H
        
        #include "comp2024.h"
        #include "lex.yy.h"

        #define MAX_STK 128

        extern int yylex(void);

        int yyparse(void);

        void token(int lex, Data* data);
        Data list(void);
        void calc(void);

        extern char* yytext;

        #ifdef Y_TAB_DEF
                #define Y_TAB_EXT
                
                int ip = 0;
                int op = 0;
        #else
                #define Y_TAB_EXT extern

                extern int ip;
                extern int op;
        #endif

        Y_TAB_EXT int int_stk[MAX_STK];
        Y_TAB_EXT char opt_stk[MAX_STK];
#endif
