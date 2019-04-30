#ifndef TREE_H
#define TREE_H

#include "node.h"
#include "type.h"


typedef struct tree_s {
	int type; 		    /* token type: INUM, RNUM, ID, RELOP, ADDOP, MULOP, SIGNOP, NOT, ... */
	int label;			/* Number of registers needed */
	int scope_offset;	/* ONLY ID: Number of scopes to jump when accessing var */

	union {
		int 	ival;	/* INUM */
		float 	rval; 	/* RNUM */
		node_t 	*sval; 	/* ID */
		int 	opval; 	/* RELOP: LT LE GT GE EQ NE */
						/* ADDOP: PLUS MINUS OR */
						/* MULOP: STAR SLASH AND */
	} attribute;

	struct tree_s *left;
	struct tree_s *right;
} tree_t;


/* Define Helper Functions */
tree_t *update_type(tree_t *node, tree_t *type_node);


/* Constructors */
tree_t *mktree(int type, tree_t *left, tree_t *right);

/* Special Constructors */
tree_t *mkid(node_t *);
tree_t *mkinum(int);
tree_t *mkrnum(float);
tree_t *mkarray(tree_t *lower, tree_t *upper, tree_t *type);
tree_t *mkop(int, int, tree_t *, tree_t *);
tree_t *mkprog(node_t *id, tree_t *ids, tree_t *decls, tree_t *subprog_decls, tree_t *compound_stmt);
tree_t *mksubprog(tree_t *subprog_head, tree_t *decls, tree_t *subprog_decls, tree_t *compound_stmt);
tree_t *mkfor(tree_t *var, tree_t *assign_expr, tree_t *to_expr, tree_t *do_stmt);

/* Gencode */
int max_passed_args(tree_t *node);

/* Type Stuff */
int super_type(tree_t *node);
int tree_node_type(tree_t *node);
int child_types_match(tree_t *root);
int eval_type(tree_t *root);
void check_bool(tree_t *root);

void add_args_to_func(node_t *func_node, tree_t *arg_list);
int verify_args(node_t *func_node, tree_t *arg_list);
void print_args(node_t *func_node);

int exists_return_statement(tree_t *node, tree_t *func_id);
int exists_nonlocal_assign(tree_t *node, tree_t *func_id);

/* Auxiliary */
void tree_print(tree_t *);

#endif
