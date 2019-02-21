%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "y.tab.h"
#define NUM    257
%}

whitespace      [ \t]+
number          [0-9]+

%%

"+"         {fprintf(stderr, "[OP: %c]", yytext[0]); return yytext[0];}
"*"         {fprintf(stderr, "[OP: %c]", yytext[0]); return yytext[0];}
"("         {fprintf(stderr, "[LPAREN: %c]", yytext[0]); return yytext[0];}
")"         {fprintf(stderr, "[RPAREN: %c]", yytext[0]); return yytext[0];}
{number}    {fprintf(stderr, "[NUM:%d]", yylval.ival = (int) atoi(yytext)); return NUM;}
{whitespace} ;
\n          {fprintf(stderr, "[EOL]\n", yytext[0]); return yytext[0];}
.           {fprintf(stderr, "[%c]", yytext[0]); return yytext[0];}

%%

int yyerror (char *message){
    fprintf(stderr, "ERROR: %s", message);
    exit(1);
}


