#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "scope.h"
#include "y.tab.h"
#include "type.h"

extern int yyerror (char *);
extern scope_t *top_scope;
extern node_t *BUILTIN_READ;
extern node_t *BUILTIN_WRITE;

void aux_tree_print(tree_t *t, int spaces);


/* Constructor */
tree_t *mktree(int type, tree_t *left, tree_t *right){
    tree_t *p = (tree_t *) malloc(sizeof(tree_t));
    assert (p != NULL);

    p->type = -1;
    p->label = -1;

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
    if (name_ptr == NULL) {
        yyerror("ID NOT FOUND");
    }

    tree_t *p = mktree(ID, NULL, NULL);
    p->attribute.sval = name_ptr;
    p->scope_offset = num_scope_jumps(top_scope, name_ptr->name);
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

/* Gencode Related */

/* Returns maximum number of passed arguments to a function, in the given tree root. */
/* node should be the root of a statement list, like compound_statement or optional_statments */
int max_passed_args(tree_t *node){
    int max = 0;
    int temp_num = 0;

    if (node->type == BBEGIN){
        node = node->left;
    }

    while (node != NULL){
        if (node->type != LISTOP) {
            /* Means that it's the only statement in list, break after this */
            if (node->type == PROCEDURE_CALL || node->type == FUNCTION_CALL){
                if ((temp_num = num_args(node->left->attribute.sval)) > max) max = temp_num;   
            }

            break;
        }
        else {
            /* check right, and move node*/

            /* Don't know why this would happen but hey */
            if (node->right == NULL) break;


            if (node->right->type == PROCEDURE_CALL || node->right->type == FUNCTION_CALL){
                if ((temp_num = num_args(node->right->left->attribute.sval)) > max) max = temp_num;
            }
            
            if (node->left->type != LISTOP) {
                /* check left */

                /* Again don't know why this would happen but to be safe */
                if (node->left == NULL) break;

                if (node->left->type == PROCEDURE_CALL || node->left->type == FUNCTION_CALL) {
                    if ((temp_num = num_args(node->left->left->attribute.sval)) > max) max = temp_num;
                }

                break;
            }
            else node = node->left;
        }
    }

    return max;
}

/* Type Stuff */
int super_type(tree_t *node) {return node->attribute.sval->type.super_type;}
// int tree_node_type(tree_t *node) {return node->type->tree_node_type;}

int child_types_match(tree_t *root){
    return (root->left->type == root->right->type);
}

void check_bool(tree_t *root){
    if (eval_type(root) != BOOL) {
        yyerror("Using non-boolean expression in conditional statment");
    }
}

/* Recusively returns the type of each node in the syntax tree. */
int eval_type(tree_t *root){
    if (root == NULL) return ERROR;
    int other_type;

    switch (root->type){
        case ID:
            return root->attribute.sval->type.super_type;
        case RELOP:
            if (eval_type(root->left) == eval_type(root->right)){
                return BOOL;
            }
            else return ERROR;
        case ADDOP:
        case MULOP:
            if ((other_type = eval_type(root->left)) == eval_type(root->right)){
                return other_type;
            }
            else{
                return ERROR;
            }
        case INTEGER:
        case INUM:
            /* return INTEGER */
            // fprintf(stderr, "INTEGER\n");
            return INTEGER;
        case REAL:
        case RNUM:
            return REAL;
        case ARRAY_ACCESS:
            return root->left->attribute.sval->type.super_type;
        case FUNCTION_CALL:
        case PROCEDURE_CALL:
            return root->left->attribute.sval->type.super_type;

        case NOT:
            /*
             * check if child is type bool.
             * If so, return bool.
             * Else, error.
            */
            fprintf(stderr, "NOT\n");
            if (eval_type(root->left) == BOOL) return BOOL;
            else return ERROR;

        default:
            fprintf(stderr, "BASE CASE IN EVAL_TYPE == %d\n", root->type);
            return -1;
    }
}

/* Function to update the types of entries in the symbol table */
tree_t *update_type(tree_t *node, tree_t *type_node){
    if (type_node == NULL || node == NULL) return node;

    int isArray = 0;
    int type;

    if (node->type != ID) {
        update_type(node->left, type_node);
        update_type(node->right, type_node);

        /* Original node */
        return node;
    }

    switch (type_node->type) {
        case INTEGER:
            type = INTEGER;
            break;
        case REAL:
            type = REAL;
            break;
        
        case ARRAY:
            /* Where the type lives in an array type tree */
            fprintf(stderr, "UPDATE TYPE ARRAY\n");
            type = type_node->right->type;
            isArray = 1;
            break;
            
        default:
            break;
    }

    node->attribute.sval->type.super_type = type;
    node->attribute.sval->type.array = isArray;
    if (isArray) {
        node->attribute.sval->array_lower_bound = type_node->left->left->attribute.ival;
        node->attribute.sval->array_upper_bound = type_node->left->right->attribute.ival;
    }

    /* Original node */
    return node;
}

/*
 * Creates linked list of arg_node_t entries, rooted at func_node, 
 * which represents the argument structure of the passed func_node.
*/
void add_args_to_func(node_t *func_node, tree_t *arg_list){
    /*
        SHOULD NEVER MALLOC/FREE WITH ARG_LIST

        arg_list LISTOP is in left child, 
        picked off item is in right child.

        Each leaf node should be an ID
    */

    if (arg_list == NULL) {
        func_node->func_arguments = NULL;
        return;
    }

    arg_node_t *curr_node     = malloc(sizeof(arg_node_t));
    tree_t     *curr_arg      = arg_list;

    func_node->func_arguments = curr_node;
    while(curr_arg != NULL){
        /*
         * Cases for each node are:
         *  arg_list is NULL
         *  right child is ID, left child is LISTOP
         *  right child is ID, left child is ID
         *  curr_node is an ID, both children NULL
         */
        
        if (curr_arg->type == ID){
            curr_node->type.super_type = curr_arg->attribute.sval->type.super_type;
            curr_node->next = NULL;
            break;
        }
        else curr_node->type.super_type = curr_arg->right->attribute.sval->type.super_type;

        if (curr_arg->left != NULL){
            curr_node->next = malloc(sizeof(arg_node_t));
            curr_node = curr_node->next;

            /* shouldn't be needed, cuz of ID base case above */
            // if (tree_node_type(curr_arg->left) == ID){
            //     curr_node->type.super_type = curr_arg->left->attribute.sval->type;
            //     curr_node->next = NULL;
            //     // curr_node = curr_node->next;
            //     break;
            // }
        }
        
        curr_arg = curr_arg->left;
    }

    /* END? */
}

void print_args(node_t *func_node){
    fprintf(stderr, "BEGIN PRINT ARGUMENTS FOR: %s\n", func_node->name);
    arg_node_t *curr_node = func_node->func_arguments;

    while(curr_node != NULL){
        // fprintf(stderr, "%s\n", curr_node->entry->name);
        fprintf(stderr, "%d\n", curr_node->type.super_type);
        curr_node = curr_node->next;
    }
    fprintf(stderr, "END PRINT ARGUMENTS FOR: %s\n", func_node->name);
}

/**
 * Verifies that arg_list matches the format of func_node->func_arguments.
 * Returns 1 if arg_list is of the correct types and length.
 * Returns 0 otherwise.
*/
int verify_args(node_t *func_node, tree_t *arg_list){
    /**
     * arg_list is expression list
     * NEVER DESCEND INTO CHILD OF AN A NON LISTOP NODE
     * 
     * Cases for each arg node are:
     * 1. curr_node is NULL
     * 2. curr_node is expr (not LISTOP)
     * 3. curr_node is LISTOP, right child is expr, left child is LISTOP
     * 4. curr_node is LISTOP, right child is expr, left child is expr
     */

    /* TEMPORARY FOR READ AND WRITE */
    if (func_node == BUILTIN_READ || func_node == BUILTIN_WRITE) return 1;
    arg_node_t *curr_node     = func_node->func_arguments;
    tree_t     *curr_arg      = arg_list;
    int correct = 1;
    while(correct){
        if (curr_node == NULL) fprintf(stderr, "curr_node == NULL\n");
        if (curr_arg == NULL) fprintf(stderr, "curr_arg == NULL\n");

        /* Case 1 */
        if (curr_node == NULL && curr_arg == NULL) break;
        if (curr_node == NULL || curr_arg == NULL) {
            correct = 0;
            break;
        }

        /* Case 2 */
        else if (curr_arg->type != LISTOP){
            fprintf(stderr, "CASE 2\n");
            
            if (eval_type(curr_arg) == curr_node->type.super_type){
                if (curr_node->next != NULL) correct = 0;
            }
            else correct = 0;

            /* Always break because its the end of expr_list */
            break;
        }
        
        /* Case 3 */
        else if (curr_arg->left->type == LISTOP){
            fprintf(stderr, "CASE 3\n");

            if (eval_type(curr_arg->right) == curr_node->type.super_type){
                curr_node = curr_node->next;
                curr_arg = curr_arg->left;
            }
            else{
                correct = 0;
                break;
            }
        }

        /* Case 4 */
        else {
            fprintf(stderr, "CASE 4\n");
            // fprintf(stderr, "curr_node == %s\n", curr_node->entry->name);
            // if (scope_search_all(top_scope, curr_node->entry->name) == NULL) fprintf(stderr, "scope_search_all == NULL\n");

            if (eval_type(curr_arg->right) == curr_node->type.super_type) curr_node = curr_node->next;
            else {
                correct = 0;
                break;
            }
            
            if (curr_node == NULL) correct = 0;
            else if (eval_type(curr_arg->left) != curr_node->type.super_type) correct = 0;

            /* Always break because no more LISTOP */
            break;
        }
    }

    return correct;
}

/* Check if there's an ASSIGNOP statement, with left child being the var referenced by func_id */
/* Returns 1 if it is found, and 0 if not */
int exists_return_statement(tree_t *node, tree_t *func_id){
    /* func_id is a tree with type ID */
    /* SYMBOL TABLE ENTRY FOR func_id SHOULD BE STILL VALID */


    if (node == NULL) return 0;
    // fprintf(stderr, "TYPE IS %d\n", node->type->tree_node_type);
    if (node->type == ASSIGNOP){
        /* Left child has to be an ID */
        // fprintf(stderr, "ASSIGNOP\n");

        if (node->left->attribute.sval == func_id->attribute.sval){
            /* Assignemnt to func_id */
            return 1;
        }
        else return 0;
    }
    else {
        return exists_return_statement(node->left, func_id) || exists_return_statement(node->right, func_id); 
    }

}

int exists_nonlocal_assign(tree_t *node, tree_t *func_id){
    /* func_id is a tree with type ID */
    /* SYMBOL TABLE ENTRY FOR func_id SHOULD BE STILL VALID */

    if (node == NULL) return 0;
    if (node->type == ASSIGNOP){
        /* Left child has to be an ID */
        
        if (scope_search(top_scope, node->left->attribute.sval->name) == NULL){
            /* Checks if the non-local assignment is really just the return statement */
            if (!exists_return_statement(node, func_id)){
                /* NON-LOCAL ASSIGNMENT */
                fprintf(stderr, "%s is NON_LOCAL\n", node->left->attribute.sval->name);
                return 1;
            }
        }
        return 0;
    }
    else {
        return exists_nonlocal_assign(node->left, func_id) || exists_nonlocal_assign(node->right, func_id); 
    }
}

int count_id_list(tree_t *root) {
    if (root->type == ID) return 1;
    else return count_id_list(root->left) + count_id_list(root->right);
}

int fix_offset_for_array(tree_t *id_node, int size) {
    /* Size is upper - lower + 1 (total size of array) */
    /* Return val is the next usable offset */

    if (id_node->left == NULL && id_node->right == NULL) {
        /* Base Case */
        return id_node->attribute.sval->offset + size;
    }
    else {
        int left = fix_offset_for_array(id_node->left, size);
        id_node->right->attribute.sval->offset = left;

        return id_node->right->attribute.sval->offset + size;
    }
}


/* TREE PRINT */
void tree_print(tree_t *t){
    fprintf(stderr, "\n---BEGIN PRINT TREE---\n");
    aux_tree_print(t, 0);
    fprintf(stderr, "\n---END PRINT TREE---\n");
}

void aux_tree_print(tree_t *t, int spaces){
    node_t *idNode;
    int increment = 2;

    if (t == NULL) return;

    for (int i=0; i < spaces; i++){
        if (i%increment == 0){
            fprintf(stderr, "|");
        } 
        fprintf(stderr, " ");
    }
    // fprintf(stderr, "type == %d\n", t->type);
    if (t->label != -1) fprintf(stderr, "{%d} ", t->label);
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
        case INTEGER:
            fprintf(stderr, "[INTEGER]\n");
            break;
        case RNUM:
            fprintf(stderr, "[RNUM: %f]\n", t->attribute.rval);
            break;
        case REAL:
            fprintf(stderr, "[REAL]\n");
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
        case ARRAY:
            fprintf(stderr, "[ARRAY]\n");
            break;
        case DOTDOT:
            fprintf(stderr, "[..]\n");
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
            fprintf(stderr, "[ID: %s [offset: %d] [scope_offset: %d] (type: %d)]", t->attribute.sval->name, t->attribute.sval->offset, t->scope_offset, t->attribute.sval->type.super_type);
            if (t->attribute.sval->type.array) { 
                fprintf(stderr, "<%d, %d>\n", t->attribute.sval->array_lower_bound, t->attribute.sval->array_upper_bound);
            }
            else fprintf(stderr, "\n");
            break;
        
        default:
            fprintf(stderr, "---Error at node type %d---", t->type);
            // yyerror("Error in tree_print");
    }
    // fprintf(stderr, "\n");

    aux_tree_print(t->left, spaces+increment);
    aux_tree_print(t->right, spaces+increment);
}
