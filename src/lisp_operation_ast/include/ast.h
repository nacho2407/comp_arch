#ifndef AST_H
        #define AST_H

        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        #define MAX_STK 128
        #define TAB_SIZE 8

        typedef enum _n_type {
                INT,
                SYM,
                STR,
                FUNC,
                NIL
        } n_type;

        typedef struct _node* node;
        struct _node {
                n_type type;

                union {
                        int ival;
                        char* sval;
                };

                int is_sval;

                node left;
                node right;
        };

        #ifdef AST_DEF
                struct _node nil = { .type = NIL, .ival = 0, .is_sval = 0, .left = 0, .right = 0 };

                #define AST_EXT
        #else
                extern struct _node nil;

                #define AST_EXT extern
        #endif

        node mk_int_node(int n);
        node mk_sym_node(char* s);
        node mk_str_node(char* s);
        node mk_func_node(char* op, node left, node right);
        void free_node(node n);
        void print_tree(node n, int depth);

        AST_EXT char** func_stk;
        AST_EXT int sp;
#endif
