%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "y.tab.h"

extern int yyerror(char*);
extern int yylex();

#define ECHO 1

%}

%union {
    int ival;   /* INUM */
    float rval; /* RNUM */
    int opval;  /* RELOP ADDOP MULOP */
    char *sval; /* ID */
    /*********************************/
    tree_t *tval;
}

%token PROGRAM
%token BBEGIN END
%token VAR
%token PROCEDURE FUNCTION
%token ARRAY OF
%token INTEGER REAL
%token RESULT

%token IF THEN ELSE
%token WHILE DO

%token ASSIGNOP
%token <opval> RELOP
%token EQ NE LT LE GT GE
%token <opval> ADDOP
%token PLUS MINUS OR
%token <opval> MULOP
%token STAR SLASH DIV MOD AND
%token NOT

%token DOTDOT
%token <sval> ID
%token <ival> INUM
%token <rval> RNUM

%token COMMA

%token ARRAY_ACCESS
%token FUNCTION_CALL
%token PROCEDURE_CALL





%type <tval> program;
%type <tval> compound_statement;
%type <tval> optional_statements;
%type <tval> statement_list;
%type <tval> statement;
%type <tval> matched_statement;
%type <tval> unmatched_statement;
%type <tval> variable;
%type <tval> procedure_statement;
%type <tval> expression_list;
%type <tval> expression;
%type <tval> simple_expression;
%type <tval> term;
%type <tval> factor;

%type <ival> sign;

%%

start
    : program   {}
    ;

program
    :
    PROGRAM ID '(' identifier_list ')' ';'
    declarations
    subprogram_declarations
    compound_statement
    '.'
    {/* print tree */}
    ;

identifier_list
    : ID                        {/* $$ = mkid(symtab_insert($1)); */}
    | identifier_list ',' ID    {/* mktree(COMMA, $1, mkid(symtab_insert($3))); */}
    ;

declarations
    : declarations VAR sub_declarations {/* check his notes if unsure*/}
    | /* empty */
    ;

sub_declarations
    : sub_declarations identifier_list ':' type ';' {update_type_information($2, $4);}
        {/* Do below, and add sub_declarations as the next pointer */}
    | identifier_list ':' type ';'
        {/* $$ = make_decl_node(make_ident_list($1), $3). make_ident_list also counts num of items in list. */}
    ;

type
    : standard_type                                         {$$ = NULL; }
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type       {$$ = NULL; }
    ;

standard_type
    : INTEGER
    | REAL
    ;

subprogram_declarations
    : subprogram_declarations subprogram_declaration ';'
    | /* empty */
    ;

subprogram_declaration
    : subprogram_head
    declarations
    subprogram_declarations
    compound_statement
		{ /* pop current scope */ }
    ;

subprogram_head
    : FUNCTION ID { /* push new scope */  } arguments ':' maybe_result standard_type ';'
    | PROCEDURE ID arguments ';'
    ;

maybe_result
    : RESULT
    | /* empty */
    ;

arguments
    : '(' parameter_list ')'
    | /* empty */
    ;

parameter_list
    : identifier_list ':' type          {}
    | parameter_list ';' identifier_list ':' type
    ;

compound_statement
    : BBEGIN optional_statements END    {$$ = $2; /* might need to tag as begin/end block */}
    ;

optional_statements
    : statement_list    {$$ = $1;}
    | /* empty */       {$$ = NULL;}
    ;

statement_list
    : statement                         {$$ = $1; }
    | statement_list ';' statement      {$$ = mktree(COMMA, $1, $3); }
    ;

statement
    : matched_statement
    | unmatched_statement
    ;

matched_statement
    : IF expression THEN matched_statement ELSE matched_statement
        {$$ = mktree(IF, $2, mktree(THEN, $4, $6));}
    | variable ASSIGNOP expression      {$$ = mktree(ASSIGNOP, $1, $3);}
    | procedure_statement       {$$ = $1;}
    | compound_statement        {$$ = $1;}
    | WHILE expression DO statement /* causes shift/reduce conflict */  
        {$$ = mktree(WHILE, $2, $4); }
    ;

unmatched_statement
    : IF expression THEN statement                                      {$$ = mktree(IF, $2, $4);}
    | IF expression THEN matched_statement ELSE unmatched_statement     {$$ = mktree(IF, $2, mktree(THEN, $4, $6));}
    ;

/* ------------------below here should use symtab_search with IDs? */

variable
    : ID                        {/* return entry in symbol table to be assigned */}
    | ID '[' expression ']'     {/* Array access*/}
    ;

procedure_statement
    : ID                            {$$ = mkid($1);}
    | ID '(' expression_list ')'    {$$ = mktree(ARRAY_ACCESS, mkid($1), $3);}
    ;

expression_list
    : expression                        {$$ = $1;}
    | expression_list ',' expression    {$$ = mktree(COMMA, $1, $3);}
    ;

expression
    : simple_expression     {$$ = $1;}
    | simple_expression RELOP simple_expression {/* mkop with RELOP */}
    ;

simple_expression
    : term                          { $$ = $1; }
    | sign term                     {/* mkop with add and null right child */}
    | simple_expression ADDOP term  { $$ = mkop(ADDOP, $2, $1, $3); }
    ;
    /* issue here, sign should be lower than ADDOP */

term
    : factor                {/* Return factor */ $$ = $1; }
    | term MULOP factor     {$$ = mkop(MULOP, $2, $1 ,$3);}
    ;

factor
    : ID                            { $$ = mkid(symtab_search($1));}
    | ID '[' expression ']'         { $$ = mktree(ARRAY_ACCESS, mkid(symtab_search($1)), $3);}
    | ID '(' expression_list ')'    { $$ = mktree(FUNCTION_CALL, mkid(symtab_search($1)), $3);}
    | INUM                          { $$ = mkinum($1); }
    | RNUM                          { $$ = mkrnum($1); }
    | '(' expression ')'            { $$ = $2;}
    | NOT factor                    { $$ = mktree(NOT, $2, NULL);}
    ;

sign
    : '+' {$$ =  1;}
    | '-' {$$ = -1;}
    ;

%%

int main() {
    yyparse();
}
