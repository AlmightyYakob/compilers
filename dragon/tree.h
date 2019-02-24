#ifndef TREE_H
#define TREE_H

// Define Node Types

typedef struct statement_s {
	// Fill in with stuff
	// union of different types
	// ex. if then, assign, while, etc. 

	// Pointer to next statement
	statement *next;

} statement;

typedef struct statement_list_s {
	int numStatements;
	statement *start;
} statement_list;


typedef struct identifier_s {
	char *ident;
	identifier *next;
} identifier;

typedef struct identifier_list_s {
	int numIdents;
	identifier *start;
} identifier_list;


typedef struct declaration_node_s {
	int type;	// Data type of all variables declared with it
	identifier_list vars;
} declaration_node;

typedef struct subprogram_declaration_node_s {
	// Way to differentiate between func and procedure.
	// Might make 2 different structs for this
	int type;

	// Function arguments
	char **vars

	// Token that represents return type of function
	int return_type

	// List of declarations
	declaration_node *declarations;

	// List of subprogram declarations
	subprogram_declaration_node *subprogram_declarations;

	// Compound statments - just list of statements
	statement_list statements;

} subprogram_declaration_node;

typedef struct subprogram_declaration_list_s {
	int numSubProgramDeclarations;
	subprogram_declaration_node *start;

} subprogram_declaration_list;


typedef struct program_node_s {
	char *name;
	identifier_list args;
	declaration_node *declarations;

	// Subprogram declarations
	subprogram_declaration_node *subprogram_declarations;

	// compound statement - just list of statements
	statement_list statements;

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
