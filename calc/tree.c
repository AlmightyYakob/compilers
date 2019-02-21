#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"

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
        case NUM:
            return t->attribute;
        default:
            fprintf(stderr, "Tree Eval: unknown type %d\n", t->type);
            exit(1);
    }
}