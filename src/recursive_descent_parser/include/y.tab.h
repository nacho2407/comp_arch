#ifndef Y_TAB_H
        #define Y_TAB_H

        #include "comp2024.h"
        #include "lex.yy.h"

        #define MAX_BUF 128

        int yyparse(void);
        Data token(void);
        void whitespace(void);
        Data integer(void);
        void non_zero(void);
        void digit(void);
        Data synonym(void);
        void non_digit(void);
        void alphabet(void);
        Data list(void);

        #ifdef Y_TAB_DEF
                #define Y_TAB_EXT

                int bufp = 0;
        #else
                #define Y_TAB_EXT extern 

                extern int bufp;
        #endif

        Y_TAB_EXT char* buf;
#endif
