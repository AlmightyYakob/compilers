%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "scope.h"
#include "tree.h"
#include "type.h"
#include "gencode.h"
#include "y.tab.h"

extern int yyerror(char*);
extern int yylex();

extern scope_t *top_scope;
extern tree_t *TREE_ROOT;
extern node_t *BUILTIN_READ;
extern node_t *BUILTIN_WRITE;

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
%token ANY
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


%token ERROR
%token BOOL





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

%type <tval> sign;

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
    {
        $$ = TREE_ROOT = mkprog(scope_insert(top_scope, $2), $4, $7, $8, $9);

        // int max_passed = max_passed_args($9);
        // fprintf(stderr, "MAX PASSED == %d\n", max_passed);
        // int record_size = num_local_vars(top_scope)*4 + max_passed + VAR_OFFSET;
        int record_size = num_local_vars(top_scope)*VAR_SIZE + VAR_OFFSET;

        // gen_prologue($2, record_size);
        gen_prologue($$->left, record_size);
        gen_stmt($9);
        gen_epilogue($$->left, record_size);
    }
    ;

identifier_list:
    ID {
        if (scope_search(top_scope, $1) != NULL) {
            yyerror("ID defined twice");
        }
        $$ = mkid(scope_insert(top_scope, $1));
    }
    | identifier_list ',' ID
        {
            if (scope_search(top_scope, $3) != NULL) {
                yyerror("ID defined twice");
            }
            $$ = mktree(LISTOP, $1, mkid(scope_insert(top_scope, $3)));
        }
    ;

declarations:
    declarations VAR sub_declarations       {$$ = mktree(LISTOP, $1, $3);}
    | /* empty */                           {$$ = NULL; }
    ;

sub_declarations:
    sub_declarations identifier_list ':' type ';' {
        $$ = mktree(LISTOP, $1, update_type($2, $4));
        
        if ($4->type == ARRAY) {
            int size = $4->left->right->attribute.ival - $4->left->left->attribute.ival + 1;
            fprintf(stderr, "------ARRAY----\n");
            fprintf(stderr, "Size: %d\n", size);
            fprintf(stderr, "Offset before: %d\n", top_scope->curr_offset);
            top_scope->curr_offset = fix_offset_for_array($2, size);
            fprintf(stderr, "Offset after: %d\n", top_scope->curr_offset);
        }
    }
    | identifier_list ':' type ';' {
        $$ = update_type($1, $3);

        if ($3->type == ARRAY) {
            int size = $3->left->right->attribute.ival - $3->left->left->attribute.ival + 1;
            fprintf(stderr, "------ARRAY----\n");
            fprintf(stderr, "Size: %d\n", size);
            fprintf(stderr, "Offset before: %d\n", top_scope->curr_offset);
            top_scope->curr_offset = fix_offset_for_array($1, size);
            fprintf(stderr, "Offset after: %d\n", top_scope->curr_offset);
        }
    }
    ;

type:
    standard_type                                           {$$ = $1; }
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type       {$$ = mkarray(mkinum($3), mkinum($5), $8);}
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
            $$ = mksubprog($1, $2, $3, $4);
            
            /*
                Check for return statement if function,
                Check for lack thereof if a procedure
             */
            
            if ($1->type == FUNCTION){
                if (!exists_return_statement($4, $1->left)){
                    yyerror("Missing function return statement");
                }

                /* Check for non-local assigns */
                if (exists_nonlocal_assign($4, $1->left) == 1){
                    yyerror("Assignment to non-local variable in function body");
                }
            }
            else if ($1->type == PROCEDURE) {
                if (exists_return_statement($4, $1->left)){
                    yyerror("Illegal procedure return statement");
                }
            }
            else {
                /* This should literally never happen */
            }

            // int max_passed = max_passed_args($4);
            // fprintf(stderr, "%s: MAX PASSED == %d\n", $1->left->attribute.sval->name, max_passed);
            // int record_size = num_local_vars(top_scope)*4 + max_passed + VAR_OFFSET;
            int record_size = num_local_vars(top_scope)*VAR_SIZE + VAR_OFFSET;

            gen_prologue($1, record_size);
            gen_stmt($4);
            gen_epilogue($1, record_size);


            /* pop current scope */ 
            fprintf(stderr, "-----------POP--------\n");
            top_scope = pop_scope(top_scope);
        }
    ;

subprogram_head:
    FUNCTION ID {
            if (scope_search(top_scope, $2) != NULL) {
                yyerror("Function ID defined twice");
            }
            
            node_t *func_id = scope_insert(top_scope, $2);
            fprintf(stderr, "-----------PUSH--------\n");
            top_scope = push_scope(top_scope);
    } arguments ':' maybe_result standard_type ';' { 
            /* push new scope and update type info of ID */

            node_t *func_id_node = scope_search_all(top_scope, $2);
            add_args_to_func(func_id_node, $4);

            $$ = mktree(FUNCTION, update_type(mkid(func_id_node), $7), $4);
    }
    | PROCEDURE ID {
        if (scope_search(top_scope, $2) != NULL) {
            yyerror("Procedure ID defined twice");
        }
        node_t *proc_id = scope_insert(top_scope, $2);
        fprintf(stderr, "-----------PUSH--------\n");
        top_scope = push_scope(top_scope);
    } arguments ';' {

        node_t *proc_id_node = scope_search_all(top_scope, $2);
        add_args_to_func(proc_id_node, $4);
        $$ = mktree(PROCEDURE, mkid(proc_id_node), $4);

        if (proc_id_node == BUILTIN_WRITE) {
            gen_write_format();
        }
    }
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
        {
            $$ = update_type($1, $3);
            // fprintf(stderr, "NUM IDs: %d\n", count_id_list($1));
            /* Add to offset for each ID if type is array */
        }
    | parameter_list ';' identifier_list ':' type
        {
            $$ = mktree(LISTOP, $1, update_type($3, $5));
            // fprintf(stderr, "NUM IDs: %d\n", count_id_list($3));
        }
    ;

compound_statement:
    BBEGIN optional_statements END {
        $$ = mktree(BBEGIN, $2, mktree(END, NULL, NULL)); 

        /* Call label alg on $2 */
        label_node($2, 1);
    }
    ;

optional_statements:
    statement_list      {$$ = $1;}
    | /* empty */       {$$ = NULL;}
    ;

statement_list:
    statement                           {$$ = $1; /* gen_stmt($1); */}
    | statement_list ';' statement      {$$ = mktree(LISTOP, $1, $3); }
    ;

statement:
    matched_statement       {$$ = $1;}
    | unmatched_statement   {$$ = $1;}
    ;

matched_statement:
    IF expression THEN matched_statement ELSE matched_statement
        {   
            /* Check that expression is BOOLEAN */
            $$ = mktree(IF, $2, mktree(THEN, $4, $6));
        }
    | variable ASSIGNOP expression
        {
            /* Check that variable and expression are the same type */
            /* Add check for functions not updating non-local variables */
            if (eval_type($1) != eval_type($3)){
                yyerror("Mismatched types in assignment");
            }

            $$ = mktree(ASSIGNOP, $1, $3);
        }
    | procedure_statement
        {$$ = $1;}
    | compound_statement
        {$$ = $1;}
    | WHILE expression DO matched_statement /* statement instead of matched_statement causes shift/reduce conflict */  
        {
            /* Check that expression is BOOLEAN */
            check_bool($2);
            $$ = mktree(WHILE, $2, $4); 
        }
    | FOR variable ASSIGNOP simple_expression TO simple_expression DO matched_statement
        {
            /* Check that types of variable? and both expressions match */

            if (eval_type($2) != eval_type($4) || eval_type($4) != eval_type($6)){
                yyerror("Type mismatch in FOR expression");
            }

            $$ = mkfor($2, $4, $6, $8); 
        }
    ;

unmatched_statement:
      IF expression THEN statement                                      
        {
            /* Check that expression is BOOLEAN */

            check_bool($2);
            $$ = mktree(IF, $2, $4);
        }
    | IF expression THEN matched_statement ELSE unmatched_statement     
        {
            /* Check that expression is BOOLEAN */

            check_bool($2);
            $$ = mktree(IF, $2, mktree(THEN, $4, $6));
        }
    ;

/* ------------------below here should use mkid(symtab_search) for IDs? */

variable:
      ID
        {
            $$ = mkid(scope_search_all(top_scope, $1));

            if ($$->attribute.sval->type.array) {
                yyerror("No index passed to array variable");
            }
        }
    | ID '[' expression ']'
        {
            /* Array access */
            /* Check that expression is of type INTEGER */
            if (scope_search_all(top_scope, $1) != NULL){
                /* Check that ID is of type array */
                if (!(scope_search_all(top_scope, $1)->type.array)) {
                    yyerror("Indexing non-array variable");
                }
            }

            if (eval_type($3) != INTEGER){
                yyerror("Array Access with non-integer type");
            }

            // $$ = mkid(scope_search_all(top_scope, $1)); 
            $$ = mktree(ARRAY_ACCESS, mkid(scope_search_all(top_scope, $1)), $3);
        }
    ;

procedure_statement:
      ID                            {$$ = mkid(scope_search_all(top_scope, $1));}
    | ID '(' expression_list ')'    
        {   
            /* Verify that parameters are correct in order and type */
            if (!verify_args(scope_search_all(top_scope, $1), $3)) {
                yyerror("Incorrect parameters to procedure call");
            }

            $$ = mktree(PROCEDURE_CALL, mkid(scope_search_all(top_scope, $1)), $3);
        }
    ;

expression_list:
    expression                          {$$ = $1;}
    | expression_list ',' expression    {$$ = mktree(LISTOP, $1, $3);}
    ;

expression:
    simple_expression                           {$$ = $1; }
    | simple_expression RELOP simple_expression {$$ = mkop(RELOP, $2, $1, $3); /* BOOLEAN TYPE */}
    ;

simple_expression:
    /* Here, need to check type of all children, to ensure matching */
    term                                { $$ = $1; }
    | sign term                         { $$ = mkop(MULOP, STAR, $1, $2); }
    | simple_expression ADDOP term      { $$ = mkop(ADDOP, $2, $1, $3); }
    ;
    /* issue here, sign should be lower than ADDOP */

term:
    factor                  {$$ = $1; }
    | term MULOP factor     {$$ = mkop(MULOP, $2, $1 ,$3);}
    ;

factor:
    ID                              
        { $$ = mkid(scope_search_all(top_scope, $1)); }
    | ID '[' expression ']'
        {
            if (scope_search_all(top_scope, $1) != NULL){
                /* Check that ID is of type array */
                if (!(scope_search_all(top_scope, $1)->type.array)) {
                    yyerror("Indexing non-array variable");
                }
            }

            if (eval_type($3) != INTEGER){
                yyerror("Array Access with non-integer type");
            }

            $$ = mktree(ARRAY_ACCESS, mkid(scope_search_all(top_scope, $1)), $3);
        }
    | ID '(' expression_list ')'
        {
            /* Check that types of expression_list matches the types in func declaration */
            /* Set super_type of this node to be return type of func */
            
            /* Check that ID is a function, not a procedure */
            /* Checking that type is -1 isn't exactly correct */
            if (scope_search_all(top_scope, $1) != NULL && scope_search_all(top_scope, $1)->type.super_type == -1){
                yyerror("Procedure used as factor in expression (procedures can't return values)");
            }

            /* Verify that parameters are correct in order and type */
            if (!verify_args(scope_search_all(top_scope, $1), $3)) yyerror("Incorrect parameters to function call");
            
            $$ = mktree(FUNCTION_CALL, mkid(scope_search_all(top_scope, $1)), $3);
            $$->type = FUNCTION_CALL;
        }
    | INUM                          { $$ = mkinum($1); }
    | RNUM                          { $$ = mkrnum($1); }
    | '(' expression ')'            { $$ = $2;}
    | NOT factor                    { $$ = mktree(NOT, $2, NULL);}
    ;

/* Not sure what to do with sign */

sign
    : '+' {$$ =  mkinum(1); }
    | '-' {$$ =  mkinum(-1); }
    ;



%%

scope_t *top_scope;
node_t *BUILTIN_READ;
node_t *BUILTIN_WRITE;
tree_t *TREE_ROOT;

int CURRENT_LINE_NUM = 1;
FILE *OUTFILE;

int main(int argc, const char* argv[]) {
    top_scope = mkscope();
    OUTFILE = fopen("out.s", "w");

    /* Built-in functions */
    BUILTIN_READ  = scope_insert(top_scope, "read");
    BUILTIN_WRITE = scope_insert(top_scope, "write");

    /* setup single argument for read and write, of any type */

    gen_file_header();
    yyparse();
    gen_main(TREE_ROOT->left->left->attribute.sval->name);
    gen_main_footer();
    /* Could call gcc here? */

    fclose(OUTFILE);
}
