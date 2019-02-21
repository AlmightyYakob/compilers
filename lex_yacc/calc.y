%{
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tree.h"
#include "y.tab.h"

extern int yylex();
extern int yyerror (char *);

#define ECHO 0
%}

%union {
    /* Attribute channel (with scanner) */
    int ival;       /* Attribute for NUM */

    /* Semantic Attributes */
    tree_t *tval;   /* Attribute for syntax trees */
}

%token <ival> NUM

%left '+'
%left '-'
%left '*'
%left '/'

%type <tval> expr

%%

start: 
    expr '\n'
    {
        if (ECHO) tree_print($1);
        fprintf(stderr, "Value = %d\n", tree_eval($1));
        exit(0);
    }
    ;

expr: 
      expr '+' expr { $$ = mktree('+', $1, $3); }
    | expr '-' expr { $$ = mktree('-', $1, $3); }
    | expr '*' expr { $$ = mktree('*', $1, $3); }
    | expr '/' expr { $$ = mktree('/', $1, $3); }
    | '(' expr ')'  { $$ = $2; }
    | NUM           { $$ = mktree(NUM, NULL, NULL); $$->attribute = $1; }
    ;
%%

int main(){
    yyparse();
}