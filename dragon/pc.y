%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "y.tab.h"

extern int yyerror(char*);
extern int yylex();
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

%token IF THEN ELSE WHILE DO

%token ASSIGNOP
%token RELOP EQ NE LT LE GT GE
%token ADDOP PLUS MINUS OR
%token MULOP STAR SLASH AND
%token NOT

%token DOTDOT
%token ID 
%token INUM
%token RNUM

%%

program: 
    PROGRAM ID '(' identifier_list ')' ';'
    declarations
    subprogram_declarations
    compound_statement
    '.'
    ;

identifier_list
    : ID
    | identifier_list ',' ID
    ;


declarations
    : declarations VAR identifier_list ':' type ';'
    | /* empty */
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
		{ /* pop current scope */  }
    ;

subprogram_head
    : FUNCTION ID { /* push new scope */  } arguments ':' standard_type ';'
    | PROCEDURE ID arguments ';'
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
    : variable ASSIGNOP expression
    | procedure_statement
    | compound_statement
    | IF expression THEN statement ELSE statement
    | WHILE expression DO statement
    ;

variable
    : ID
    | ID '[' expression ']'
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
    | sign term         /* issue here, sign should be lower than ADDOP */
    | simple_expression ADDOP term
    ;

term
    : factor
    | term MULOP factor
    ;

factor
    : ID
    | ID '[' expression ']'
    | ID '(' expression_list ')'
    | INUM
    | RNUM
    | '(' expression ')'
    | NOT factor
    ;
    
sign
    : '+'
    | '-'
    ;

%%
