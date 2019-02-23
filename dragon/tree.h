#ifndef TREE_H
#define TREE_H

// Define Node Types

typedef struct identifier_list_s {
	int numVars;
	char **vars;
} identifier_list;

typedef struct declaration_node_s {
	int type;	// Data type of all variables declared with it
	identifier_list vars;

} declaration_node;


typedef struct program_node_s {
	char *name;
	identifier_list args;
	declaration_node *declarations;

	// Subprogram declarations
	// compound statement - just list of statements

} program_node;



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
