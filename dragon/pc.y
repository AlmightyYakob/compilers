%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
%token <opval> RELOP EQ NE LT LE GT GE
%token <opval> ADDOP PLUS MINUS OR
%token <opval> MULOP STAR SLASH DIV MOD AND
%token NOT

%token DOTDOT
%token <sval> ID
%token <ival> INUM
%token <rval> RNUM

%%

program
    :
    PROGRAM ID '(' identifier_list ')' ';'
    declarations
    subprogram_declarations
    compound_statement
    '.'
    {}
    ;

identifier_list
    : ID                        { /* return ident with next being NULL */ make_identifier($1, NULL); }
    | identifier_list ',' ID    { /* return ident with next being the ident_list*/ make_identifier($3, $1)}
    ;

declarations
    : declarations VAR sub_declarations
    | /* empty */
    ;

sub_declarations
    : sub_declarations identifier_list ':' type ';'
        {/* Do below, and add sub_declarations as the next pointer */}
    | identifier_list ':' type ';'
        {/* $$ = make_decl_node(make_ident_list($1), $3). make_ident_list also counts num of items in list. */}
    ;

type
    : standard_type
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type
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
    : identifier_list ':' type
    | parameter_list ';' identifier_list ':' type
    ;

compound_statement
    : BBEGIN optional_statements END
    ;

optional_statements
    : statement_list
    | /* empty */
    ;

statement_list
    : statement
    | statement_list ';' statement
    ;

statement
    : matched_statement
    | unmatched_statement
    ;

matched_statement
    : IF expression THEN matched_statement ELSE matched_statement
    | variable ASSIGNOP expression
    | procedure_statement
    | compound_statement
    | WHILE expression DO statement     /* causes shift/reduce conflict */
    ;

unmatched_statement
    : IF expression THEN statement
    | IF expression THEN matched_statement ELSE unmatched_statement
    ;

variable
    : ID                        {/* return entry in symbol table to be assigned */}
    | ID '[' expression ']'     {/* Dunno what this is for */}
    ;

procedure_statement
    : ID
    | ID '(' expression_list ')'
    ;

expression_list
    : expression
    | expression_list ',' expression
    ;

expression
    : simple_expression
    | simple_expression RELOP simple_expression
    ;

simple_expression
    : term
    | sign term
    | simple_expression ADDOP term
    ;
    /* issue here, sign should be lower than ADDOP */

term
    : factor                {/* Return factor */}
    | term MULOP factor     {/* Return mktree of * operator, with term and factor */}
    ;

factor
    : ID                            {/* return value of ID from symbol table */}
    | ID '[' expression ']'         {/* This might have to be removed */}
    | ID '(' expression_list ')'    {/*  */}
    | INUM                          {/* Return value of INUM */}
    | RNUM                          {/* Return value of RNUM */}
    | '(' expression ')'            {/* Pretty much just return expression */}
    | NOT factor                    {/* Negate whatever the value of factor is */}
    ;

sign
    : '+' {$$ =  1}
    | '-' {$$ = -1}
    ;

%%

int main() {
    yyparse();
}
