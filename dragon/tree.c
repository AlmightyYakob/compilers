#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "scope.h"
#include "y.tab.h"

extern int yyerror (char *);
extern scope_t *top_scope;
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

tree_t *mksubprog(tree_t *subprog_head, tree_t *decls, tree_t *subprog_decls, tree_t *compound_stmt){
    /* Left child is subprogram declarations, right is compound statement */
    tree_t *bottom = mktree(SUBPROGRAM_NODE, subprog_decls, compound_stmt);

    /* Left child is declarations, right child is bottom */
    tree_t *middle = mktree(SUBPROGRAM_NODE, decls, bottom);
    
    tree_t *root = mktree(SUBPROGRAM_ROOT, subprog_head, middle);

    return root;
}

tree_t *mkid(node_t *name_ptr) {
    if (name_ptr == NULL) return NULL;
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

tree_t *mkarray(tree_t *lower, tree_t *upper, tree_t *type){
    tree_t *range = mktree(DOTDOT, lower, upper);
    tree_t *root = mktree(ARRAY, range, type);

    return root;
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

tree_t *update_type(tree_t *node, tree_t *type_node){
    /* type is a node whose attribute equals the type */

    /*************FIX THIS FUNCTION*************************/
    if (type_node == NULL || node == NULL) return node;

    tree_t *p = node;
    
    int type;
    switch (type_node->type)
    {
        case INTEGER:
            type = INTEGER;
            break;
        case REAL:
            type = REAL;
            break;
        
        case ARRAY:
            /* change this case later*/
            type = ARRAY;
            break;
            
        default:
            break;
    }

    // fprintf(stderr, "---type == %d---\n", type);

    while (p != NULL){
        // fprintf(stderr, "IN LOOP\n");
        if (p->left == NULL && p->right == NULL) {
            // fprintf(stderr, "BOTH NULL\n");
            if (p->type == ID) p->attribute.sval->type = type;
            break;
        }
        else if (p->left->type == ID && p->right->type == ID){
            // fprintf(stderr, "BOTH ID\n");
            p->left->attribute.sval->type = p->right->attribute.sval->type = type;
            break;
        }

        if (p->left != NULL && p->left->type == LISTOP){
            /* go right and set type of the node_t struct pointed to by attribute.sval */
            // fprintf(stderr, "LEFT NULL\n");
            p->right->attribute.sval->type = type;
            // fprintf(stderr, "###set type == %d###\n", p->right->attribute.sval->type);
            p = p->left;
        }
        else if (p->right != NULL && p->right->type == LISTOP){
            /* go left and set type of the node_t struct pointed to by attribute.sval */
            // fprintf(stderr, "RIGHT NULL\n");
            p->left->attribute.sval->type = type;
            // fprintf(stderr, "###set type == %d###\n", p->left->attribute.sval->type);
            p = p->right;
        }
        else {
            // if (p->left != NULL) fprintf(stderr, "LEFT == %d\n", p->left->type);
            // if (p->right != NULL) fprintf(stderr, "RIGHT == %d\n", p->right->type);
            break;
        }
    }

    /* Original node */
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
        case SUBPROGRAM_ROOT:
            fprintf(stderr, "[SUBPROGRAM_ROOT]\n");
            break;
        case SUBPROGRAM_NODE:
            fprintf(stderr, "[SUBPROGRAM_NODE]\n");
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
        case PROCEDURE:
            fprintf(stderr, "[PROCEDURE]\n");
            break;
        case FUNCTION_CALL:
            fprintf(stderr, "[FUNCTION_CALL]\n");
            break;
        case PROCEDURE_CALL:
            fprintf(stderr, "[PROCEDURE_CALL]\n");
            break;
        case ARRAY_ACCESS:
            fprintf(stderr, "[ARRAY_ACCESS]\n");
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
            fprintf(stderr, "[ID: %s (%d)]\n", t->attribute.sval->name, scope_search_all(top_scope, t->attribute.sval->name)->type);
            break;
        
        default:
            fprintf(stderr, "---Error at node type %d---", t->type);
            // yyerror("Error in tree_print");
    }
    // fprintf(stderr, "\n");

    aux_tree_print(t->left, spaces+increment);
    aux_tree_print(t->right, spaces+increment);
}