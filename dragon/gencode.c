#include <stdio.h>
#include <stdlib.h>
#include "gencode.h"
#include "y.tab.h"

/* Wrapper for gen_expr */
void gen_stmt(tree_t *node){
    switch (node->type) {
        case IF:
            /* code */
            break;
        
        case FOR:
            /* code */
            break;
        
        case WHILE:
            /* code */
            break;
        
        case ASSIGNOP:
            /* code */
            break;

        case PROCEDURE_CALL:
            /* code */
            break;

        case BBEGIN:
            /* code */
            break;
    
        default:
            break;
    }
}

/* AKA gencode, left is 1 to represent its the left child or 0 if not */
void gen_expr(tree_t *node, int left){
    label_node(node, 1);

    /* Case 0 */
    if (left && node->left == NULL && node->right == NULL){
        if (node->type == ID) {
            /* EVENTUALLY REPLACE THIS WITH MEM LOCATION OF VAR */
            fprintf(stderr, "MOV\t%s, top(rstack)\n", node->attribute.sval->name);
        }
        else if (node->type == INUM){
            fprintf(stderr, "MOV\t%d, top(rstack)\n", node->attribute.ival);
        }
        else if (node->type == RNUM) {
            fprintf(stderr, "MOV\t%f, top(rstack)\n", node->attribute.rval);
        }
    }
    /* Case 1 */
    else if (node->right->label ==  0){
        gen_expr(node->left, 1);

        /* Replace stderr with file descriptor */
        fprintf(stderr, "%d\t%s, top(rstack)\n", node->type, node->right->attribute.sval->name);
    }
    /* Case 2 */
    else if (1 <= node->left->label < node->right->label /* and node->left->label < r */) {
        /* swap(rstack) */
        gen_expr(node->right, 0);
        /* R = pop(rstack) */
        gen_expr(node->left, 1);
        
        /* Replace stderr with file descriptor */
        fprintf(stderr, "%d\tR, top(rstack)\n", node->type);

        /* push(rstack, R) */
        /* swap(rstack) */
    }
    /* Case 3 */
    else if (1 <= node->right->label < node->left->label /* and node->right->label < r */){
        gen_expr(node->left, 1);
        /* R = pop(rstack) */
        gen_expr(node->right, 0);
        fprintf(stderr, "%d\ttop(rstack), R\n", node->type);
        /* push(rstack, R) */
    }
    /* Case 4, ignoring this for now */
    else {
        
    }
}

/* Returns 1 if the passed node is a leaf node, else 0. */
int leaf_node(tree_t *node){ return (node->left == NULL && node->right == NULL); }

/* Gencode */
int label_node(tree_t *node, int left){
    /* Probably a few more cases here */
    if (node == NULL) return 0;
    else if (node->label != -1) return node->label;

    if (leaf_node(node)) {
        if (left) node->label = 1;
        else node->label = 0;
    }
    else {
        if (label_node(node->left, 1) == label_node(node->right, 0)) node->label = label_node(node->left, 1) + 1;
        else if (label_node(node->left, 1) > label_node(node->right, 0)) node->label = label_node(node->left, 1);
        else node->label = label_node(node->right, 0);
    }

    return node->label;
}