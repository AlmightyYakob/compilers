#ifndef TREE_H
#define TREE_H

typedef struct tree_s {
	int type; 		/* token type */
	int attribute; 	/* token attribute*/

	struct tree_s *left;
	struct tree_s *right;
} tree_t;

/* Constructor */
tree_t *mktree(int type, tree_t *left, tree_t *right);

/* Auxiliary */
int tree_eval(tree_t *);
void tree_print(tree_t *);

#endif
