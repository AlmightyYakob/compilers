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

tree_t *mkprog(node_t *id, tree_t *ids, tree_t *decls, tree_t *subprog_decls, tree_t *compound_stmt){
    /* Left child is subprogram declarations, right is compound statement */
    tree_t *bottom = mktree(PROGRAM_NODE, subprog_decls, compound_stmt);

    /* Left child is declarations, right child is bottom */
    tree_t *middle = mktree(PROGRAM_NODE, decls, bottom);

    /* Left child is ID of program , right child is remaining identifier_list */
    tree_t *id_node = mktree(LISTOP, mkid(id), ids);

    tree_t *root = mktree(PROGRAM_ROOT, id_node, middle);

    return root;
}

tree_t *mkid(node_t *name_ptr) {
    // will now pass a pointer to symbol table entry, not sval
    tree_t *p = mktree(ID, NULL, NULL);
    p->attribute.sval = name_ptr;
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

tree_t *mkfor(tree_t *var, tree_t *assign_expr, tree_t *to_expr, tree_t *do_stmt){
    /*                  FOR
                       / \
                    TO    do_stmt
                  /   \
            ASSIGNOP    to_expr
            /       \
        var         assign_expr
    */

    tree_t *bottom = mktree(ASSIGNOP, var, assign_expr);
    tree_t *middle = mktree(TO, bottom, to_expr);
    tree_t *root = mktree(FOR, middle, do_stmt);
    return root;
}

tree_t *update_type_information(tree_t *node, tree_t *type){
    /* type is a node whose attribute equals the type */
    /* Need a switch statement to handle these cases  */

    // Recurse through and set type
    // Returns original node but with set types


    return node;
}

void tree_print(tree_t *t){
    fprintf(stderr, "\n---BEGIN PRINT TREE---\n");
    aux_tree_print(t, 0);
}

void aux_tree_print(tree_t *t, int spaces){
    int increment = 2;
    if (t == NULL) return;

    for (int i=0; i < spaces; i++){
        if (i%increment == 0){
            fprintf(stderr, "|");
        } 
        fprintf(stderr, " ");
    }
    // fprintf(stderr, "type == %d\n", t->type);

    switch (t->type) {
        case PROGRAM:
            fprintf(stderr, "[PROGRAM]\n");
            break;
        case PROGRAM_ROOT:
            fprintf(stderr, "[PROGRAM_ROOT]\n");
            break;
        case PROGRAM_NODE:
            fprintf(stderr, "[PROGRAM_NODE]\n");
            break;
        case BBEGIN:
            fprintf(stderr, "[BBEGIN]\n");
            break;
        case END:
            fprintf(stderr, "[END]\n");
            break;
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
            fprintf(stderr, "[INUM: %d]\n", t->attribute.ival);
            break;
        case RNUM:
            fprintf(stderr, "[RNUM: %f]\n", t->attribute.rval);
            break;
        case NOT:
            fprintf(stderr, "[NOT]\n");
            break;
        case FUNCTION:
            fprintf(stderr, "[FUNCTION]\n");
            break;
        case FUNCTION_CALL:
            fprintf(stderr, "[FUNCTION_CALL]\n");
            break;
        case PROCEDURE_CALL:
            fprintf(stderr, "[PROCEDURE_CALL]\n");
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
        case FOR:
            fprintf(stderr, "[FOR]\n");
            break;
        case TO:
            fprintf(stderr, "[TO]\n");
            break;
        case ASSIGNOP:
            fprintf(stderr, "[ASSIGNOP]\n");
            break;
        case ID:
            fprintf(stderr, "[ID: %s]\n", t->attribute.sval->name);
            break;
        
        default:
            fprintf(stderr, "---Error at node type %d---", t->type);
            // yyerror("Error in tree_print");
    }
    // fprintf(stderr, "\n");

    aux_tree_print(t->left, spaces+increment);
    aux_tree_print(t->right, spaces+increment);
}