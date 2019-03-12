#ifndef TREE_H
#define TREE_H

// #include "symbol_table.h"

/******Define Node Types******/

// Leaf node for basic types
// typedef struct {
// 	union Type {
// 		char *str;
// 		int ival;
// 		float rval;
// 	}

// 	// Pointer to value in symbol table
// } leaf_node_t;

typedef struct {
	int val;
} int_node_t;

typedef struct {
	float val;
} float_node_t;


// Nodes for basic operations
typedef struct {
	int type;
	// Other stuff
} pp;




// Statement
typedef struct statement_s {
	// Fill in with stuff
	// union of different types
	// ex. if then, assign, while, etc. 

	// Pointer to next statement
	struct statement_s *next;

} statement_node;

typedef struct statement_list_s {
	int numStatements;
	statement_node *start;
} statement_list;


// Identifier
typedef struct identifier_s {
	char *ident;
	struct identifier_s *next;
} identifier_node;

typedef struct identifier_list_s {
	int numIdents;
	identifier_node *start;
} identifier_list;


// Declaration
typedef struct declaration_node_s {
	int type;	// Data type of all variables declared with it
	identifier_list vars;
} declaration_node;

typedef struct declaration_list_s {
	int numDeclarations;
	declaration_node *start;
} declaration_list;


// Subprogram Declaration
typedef struct subprogram_declaration_node_s {
	// Way to differentiate between func and procedure.
	// Might make 2 different structs for this
	int type;

	// Function arguments
	char **vars;

	// Token that represents return type of function
	int return_type;

	// List of declarations
	declaration_node *declarations;

	// List of subprogram declarations
	struct subprogram_declaration_node_s *subprogram_declarations;

	// Compound statments - just list of statements
	statement_list statements;

} subprogram_declaration_node;

typedef struct subprogram_declaration_list_s {
	int numSubProgramDeclarations;
	subprogram_declaration_node *start;

} subprogram_declaration_list;


// Program
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
	int type; 		/* token type: INUM, RNUM, ID, RELOP, ADDOP, MULOP, SIGNOP, NOT, ... */
	union {
		int 	ival;	/* INUM */
		float 	rval; 	/* RNUM */
		char 	*sval; 	/* ID */
		int 	opval; 	/* RELOP: LT LE GT GE EQ NE */
						/* ADDOP: PLUS MINUS OR */
						/* MULOP: STAR SLASH AND */
	} attribute;

	struct tree_s *left;
	struct tree_s *right;
} tree_t;


/* Define Constructor Functions */

identifier_node make_identifier(char *name, identifier_node *next);
identifier_list make_identifier_list(identifier_node *start);




/* Constructors */
tree_t *mktree(int type, tree_t *left, tree_t *right);

/* Special Constructors */
tree_t *mkid(char *);
tree_t *mkinum(int);
tree_t *mkrnum(float);
tree_t *mkop(int, int, tree_t *, tree_t *);

/* Auxiliary */
void tree_print(tree_t *);

#endif
