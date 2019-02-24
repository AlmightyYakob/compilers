#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "y.tab.h"

extern int yyerror (char *);
void aux_tree_print(tree_t *t, int spaces);


identifier_node make_identifier(char *name, identifier_node *next){
	/* malloc ident var with name, and set next to next */
	printf("###ID = %s###", name);
}

identifier_list make_identifier_list(identifier_node *start){
	/* Set start as the start node, and count how many items */
}



tree_t *mktree(int type, tree_t *left, tree_t *right){
    tree_t *p = (tree_t *) malloc(sizeof(tree_t));
    assert (p != NULL);
    p->type = type;
    p->left = left;
    p->right = right;

    return p;
}

int tree_eval(tree_t *t){
    assert (t != NULL);

    switch (t->type){
        case '+':
            return tree_eval(t->left) + tree_eval(t->right);
        case '-':
            if (t->right != NULL){
                return tree_eval(t->left) - tree_eval(t->right);
            }
            else return -1*tree_eval(t->left);
        case '*':
            return tree_eval(t->left) * tree_eval(t->right);
        case '/':
            assert(tree_eval(t->right) != 0);
            return tree_eval(t->left) / tree_eval(t->right);
        case INUM:
            return t->attribute;
        default:
            fprintf(stderr, "Tree Eval: unknown type %d\n", t->type);
            exit(1);
    }
}

void tree_print(tree_t *t){
    aux_tree_print(t, 0);
}

void aux_tree_print(tree_t *t, int spaces){
    if (t == NULL) return;

    for (int i=0; i < spaces; i++){
        fprintf(stderr, " ");
    }

    switch (t->type) {
        case '+':
        case '-':
            fprintf(stderr, "[ADDOP]");
            break;
        case '*':
        case '/':
            fprintf(stderr, "[MULOP]");
            break;
        case INUM:
            fprintf(stderr, "[NUM: %d]", t->attribute);
            break;
        
        default:
            yyerror("Error in tree_print");
    }
    fprintf(stderr, "\n");

    aux_tree_print(t->left, spaces+4);
    aux_tree_print(t->right, spaces+4);
}