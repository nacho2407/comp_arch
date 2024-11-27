#ifndef LEX_YY_H
        #define LEX_YY_H

        #include "comp2024.h"

        int yylex(void);
        void match(int c);
        void match_condition(int begin, int end);

        #ifdef LEX_YY_DEF
                #define LEX_YY_EXT
        #else
                #define LEX_YY_EXT extern
        #endif

        LEX_YY_EXT int LA; /* Lookahead global variable */
#endif
