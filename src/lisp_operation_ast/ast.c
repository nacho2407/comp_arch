#define AST_DEF
#include "ast.h"

node mk_int_node(int n)
{
        node ret = (node) calloc(1, sizeof(struct _node));
        ret->type = INT;
        ret->ival = n;

        return ret;
}

node mk_sym_node(char* s)
{
        node ret = (node) calloc(1, sizeof(struct _node));
        ret->type = SYM;
        ret->sval = strdup(s);
        ret->is_sval = 1;

        return ret;
}

node mk_str_node(char* s)
{
        node ret = (node) calloc(1, sizeof(struct _node));
        ret->type = STR;
        ret->sval = strdup(s);
        ret->is_sval = 1;

        return ret;
}

node mk_func_node(char* func, node left, node right)
{
        node ret = (node) calloc(1, sizeof(struct _node));
        ret->type = FUNC;
        ret->sval = strdup(func);
        ret->is_sval = 1;
        ret->left = left;
        ret->right = right;

        return ret;
}

void free_node(node n)
{
        if(!n || n->type == NIL)
                return;

        if(n->left)
                free_node(n->left);
        
        if(n->right)
                free_node(n->right);

        if(n->is_sval)
                free(n->sval);

        free(n);
}

void print_tree(node n, int depth)
{
        if(!n)
                return;

        for(int i = 0; i < depth; i++)
                printf(" ");

        switch(n->type) {
                case INT:
                        printf("Int(%d)\n", n->ival);

                        break;
                case SYM:
                        printf("Sym(%s)\n", n->sval);
                        
                        break;
                case STR:
                        printf("Str(%s)\n", n->sval);

                        break;
                case FUNC:
                        printf("Func(%s)\n", n->sval);

                        if(n->left)
                                print_tree(n->left, depth + TAB_SIZE);
                        
                        if(n->right)
                                print_tree(n->right, depth + TAB_SIZE);

                        break;
                case NIL:
                        printf("NIL\n");

                        break;
        }
}
