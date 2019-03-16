%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "scope.h"
#include "tree.h"
#include "y.tab.h"

extern int yyerror(char*);
extern int yylex();

extern scope_t *top_scope;

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

%token PROGRAM PROGRAM_ROOT PROGRAM_NODE
%token SUBPROGRAM SUBPROGRAM_ROOT SUBPROGRAM_NODE
%token BBEGIN END
%token VAR
%token PROCEDURE FUNCTION
%token ARRAY OF
%token INTEGER REAL
%token RESULT

%token IF THEN ELSE
%token WHILE DO
%token FOR TO

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

%token LISTOP

%token ARRAY_ACCESS
%token FUNCTION_CALL
%token PROCEDURE_CALL





%type <tval> program;
%type <tval> identifier_list;
%type <tval> declarations;
%type <tval> sub_declarations;
%type <tval> type;                      /* Probably wrong */
%type <tval> standard_type;
%type <tval> subprogram_declarations;
%type <tval> subprogram_declaration;
%type <tval> subprogram_head;
%type <tval> arguments;
%type <tval> parameter_list;
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

//%type <ival> sign;

%%

start:
    program   {tree_print($1);}
    ;

program:
    PROGRAM ID '(' identifier_list ')' ';'
    declarations
    subprogram_declarations
    compound_statement
    '.'
    {$$ = mkprog(scope_insert(top_scope, $2), $4, $7, $8, $9); }
    ;

identifier_list:
    ID                          {$$ = mkid(scope_insert(top_scope, $1));}
    | identifier_list ',' ID    {$$ = mktree(LISTOP, $1, mkid(scope_insert(top_scope, $3)));}
    ;

declarations:
    declarations VAR sub_declarations       {$$ = mktree(LISTOP, $1, $3); }
    | /* empty */                           {$$ = NULL; }
    ;

sub_declarations:
    sub_declarations identifier_list ':' type ';'   { $$ = mktree(LISTOP, $1, $2); /*update_type_information($2, $4);*/ }
    | identifier_list ':' type ';'                  { $$ = $1; /* update_type_information($1, $3*); */}
    ;

type:
    standard_type                                           {$$ = $1; }
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type       {/* $$ = mkarray(mkinum($3), mkinum($3), $8);  */}
    ;

standard_type:
    INTEGER         {$$ = mktree(INTEGER, NULL, NULL); }
    | REAL          {$$ = mktree(REAL, NULL, NULL); }
    ;

subprogram_declarations:
    subprogram_declarations subprogram_declaration ';'      {$$ = mktree(LISTOP, $1, $2); }
    | /* empty */                                           {$$ = NULL; }
    ;

subprogram_declaration:
    subprogram_head
    declarations
    subprogram_declarations
    compound_statement
		{ 
            mksubprog($1, $2, $3, $4);
            /* pop current scope */ 
        }
    ;

subprogram_head:
    FUNCTION ID arguments ':' maybe_result standard_type ';'        { $$ = mktree(FUNCTION, mkid(scope_insert(top_scope, $2)), $3); /* push new scope and update type info of ID */}
    | PROCEDURE ID arguments ';'                                    { $$ = mktree(PROCEDURE, mkid(scope_insert(top_scope, $2)), $3); }
    ;

maybe_result:
    RESULT
    | /* empty */
    ;

arguments: 
    '(' parameter_list ')'      {$$ = $2; }
    | /* empty */               {$$ = NULL; }
    ;

parameter_list:
    identifier_list ':' type
        {$$ = $1;   /* update type information of $$ with $3 */ }
    | parameter_list ';' identifier_list ':' type
        {$$ = $1;   /* $$ = mktree(LISTOP, $1, update_type_information($3, $5)); */ }
    ;

compound_statement:
    BBEGIN optional_statements END    {$$ = mktree(BBEGIN, $2, mktree(END, NULL, NULL)); /* might need to tag as begin/end block */}
    ;

optional_statements:
    statement_list      {$$ = $1;}
    | /* empty */       {$$ = NULL;}
    ;

statement_list:
    statement                           {$$ = $1; }
    | statement_list ';' statement      {$$ = mktree(LISTOP, $1, $3); }
    ;

statement:
    matched_statement       {$$ = $1;}
    | unmatched_statement   {$$ = $1;}
    ;

matched_statement:
    IF expression THEN matched_statement ELSE matched_statement 
        {$$ = mktree(IF, $2, mktree(THEN, $4, $6));}
    | variable ASSIGNOP expression          
        {$$ = mktree(ASSIGNOP, $1, $3);}
    | procedure_statement                   
        {$$ = $1;}
    | compound_statement                    
        {$$ = $1;}
    | WHILE expression DO matched_statement /* statement instead of matched_statement causes shift/reduce conflict */  
        {$$ = mktree(WHILE, $2, $4); }
    | FOR variable ASSIGNOP simple_expression TO simple_expression DO matched_statement
        {$$ = mkfor($2, $4, $6, $8); }
    ;

unmatched_statement:
      IF expression THEN statement                                      {$$ = mktree(IF, $2, $4);}
    | IF expression THEN matched_statement ELSE unmatched_statement     {$$ = mktree(IF, $2, mktree(THEN, $4, $6));}
    ;

/* ------------------below here should use mkid(symtab_search) for IDs? */

variable:
      ID                        { $$ = mkid(scope_search_all(top_scope, $1)); /* return entry in symbol table to be assigned */ }
    | ID '[' expression ']'     { $$ = mkid(scope_search_all(top_scope, $1)); /* Array access, add part to handle expression inside brackets */ }
    ;

procedure_statement:
      ID                            {$$ = mkid(scope_search_all(top_scope, $1));}
    | ID '(' expression_list ')'    {$$ = mktree(PROCEDURE_CALL, mkid(scope_search_all(top_scope, $1)), $3);}
    ;

expression_list:
    expression                          {$$ = $1;}
    | expression_list ',' expression    {$$ = mktree(LISTOP, $1, $3);}
    ;

expression:
    simple_expression                           {$$ = $1; }
    | simple_expression RELOP simple_expression {$$ = mkop(RELOP, $2, $1, $3); }
    ;

simple_expression:
    term                                { $$ = $1; }
    /* | sign term                      { $$ = mkop(ADDOP, $?, 0, $2); } */
    | simple_expression ADDOP term      { $$ = mkop(ADDOP, $2, $1, $3); }
    ;
    /* issue here, sign should be lower than ADDOP */

term:
    factor                  {$$ = $1; }
    | term MULOP factor     {$$ = mkop(MULOP, $2, $1 ,$3);}
    ;

factor:
    ID                              { $$ = mkid(scope_search_all(top_scope, $1));}
    | ID '[' expression ']'         { $$ = mktree(ARRAY_ACCESS, mkid(scope_search_all(top_scope, $1)), $3);}
    | ID '(' expression_list ')'    { $$ = mktree(FUNCTION_CALL, mkid(scope_search_all(top_scope, $1)), $3);}
    | INUM                          { $$ = mkinum($1); }
    | RNUM                          { $$ = mkrnum($1); }
    | '(' expression ')'            { $$ = $2;}
    | NOT factor                    { $$ = mktree(NOT, $2, NULL);}
    ;

/* Not sure what to do with sign */
/* 
sign
    : '+' {$$ =  1;}
    | '-' {$$ = -1;}
    ;
 */


%%

scope_t *top_scope;

int main() {
    top_scope = mkscope();
    yyparse();
}
