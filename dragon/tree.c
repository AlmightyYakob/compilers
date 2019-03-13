#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "y.tab.h"

extern int yyerror (char *);
void aux_tree_print(tree_t *t, int spaces);


/* Constructor */
tree_t *mktree(int type, tree_t *left, tree_t *right){
    tree_t *p = (tree_t *) malloc(sizeof(tree_t));
    assert (p != NULL);
    p->type = type;
    p->left = left;
    p->right = right;

    return p;
}

/* Specialized Constructors */
tree_t *mkid(char *sval) {
    // will now pass a pointer to symbol table entry, not sval
    tree_t *p = mktree(ID, NULL, NULL);
    p->attribute.sval = strdup(sval);      /* could cause memory leak */
    return p;
}

tree_t *mkinum(int ival) {
    tree_t *p = mktree(INUM, NULL, NULL);
    p->attribute.ival = ival;
    return p;
}

tree_t *mkrnum(float rval) {
    tree_t *p = mktree(RNUM, NULL, NULL);
    p->attribute.rval = rval;
    return p;
}

tree_t *mkop(int type, int opval, tree_t *left, tree_t *right){
    tree_t *p = mktree(type, left, right);
    p->attribute.opval = opval;
    return p;
}

tree_t *update_type_information(tree_t *node, tree_t *type){
    // Recurse through and set type
    // Returns original node but with set types

    return node;
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
        case RELOP:
            fprintf(stderr, "[RELOP: %d]\n", t->attribute.opval);
            break;
        case ADDOP:
            fprintf(stderr, "[ADDOP: %d]\n", t->attribute.opval);
            break;
        case MULOP:
            fprintf(stderr, "[MULOP: %d]\n", t->attribute.opval);
            break;
        case INUM:
            fprintf(stderr, "[INUM: %d]", t->attribute.ival);
            break;
        case RNUM:
            fprintf(stderr, "[RNUM: %f]", t->attribute.rval);
            break;
        case NOT:
            fprintf(stderr, "[NOT]\n");
            break;
        case FUNCTION_CALL:
            fprintf(stderr, "[FUNCTION_CALL: %d]\n", t->attribute.opval);
            break;
        case PROCEDURE_CALL:
            fprintf(stderr, "[PROCEDURE_CALL: %d]\n", t->attribute.opval);
            break;
        case ARRAY_ACCESS:
            fprintf(stderr, "[ARRAY_ACCESS: %d]\n", t->attribute.opval);
            break;
        case LISTOP:
            fprintf(stderr, "[LISTOP]\n");
            break;
        case IF:
            fprintf(stderr, "[IF]\n");
            break;
        case THEN:
            fprintf(stderr, "[THEN]\n");
            break;
        case WHILE:
            fprintf(stderr, "[WHILE]\n");
            break;
        case ASSIGNOP:
            fprintf(stderr, "[ASSIGNOP]\n");
            break;
        
        default:
            yyerror("Error in tree_print");
    }
    fprintf(stderr, "\n");

    aux_tree_print(t->left, spaces+4);
    aux_tree_print(t->right, spaces+4);
}