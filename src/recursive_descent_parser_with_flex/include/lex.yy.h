#ifndef LEX_YY_H
        #define LEX_YY_H

        #include <ctype.h>
        #include <stdio.h>

        #define ILITERAL 301
        #define SYNONYM 302
        #define LIST_B 303
        #define LIST_E 304
        #define STRING 305
        #define OPRTR 306
        #define SIMPLE_ARITH 307

        #define MAX_BUF 128

        #ifdef LEX_YY_DEF
                #define LEX_YY_EXT
        #else
                #define LEX_YY_EXT extern
        #endif

        LEX_YY_EXT int oprtr_val;
#endif
