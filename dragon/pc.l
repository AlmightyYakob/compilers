/* Page 746 Appendix A*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "y.tab.h"
%}

number [0-9]+
ident [A-Za-z][A-Za-z0-9]*
whitespace [ \t]+


%%
{whitespace} ;

"program"       { fprintf(stderr, "[PROGRAM]"); return PROGRAM; }
"var"           { fprintf(stderr, "[VAR]"); return VAR; }
"array"         { fprintf(stderr, "[ARRAY]"); return ARRAY; }
"of"            { fprintf(stderr, "[OF]"); return OF; }
"procedure"     { fprintf(stderr, "[PROCEDURE]"); return PROCEDURE; }
"function"      { fprintf(stderr, "[FUNCTION]"); return FUNCTION; }
"begin"         { fprintf(stderr, "[BBEGIN]"); return BBEGIN; }
"end"           { fprintf(stderr, "[END]"); return END; }
"integer"       { fprintf(stderr, "[INTEGER]"); return INTEGER; }
"real"          { fprintf(stderr, "[REAL]"); return REAL; }
"if"            { fprintf(stderr, "[IF]"); return IF; }
"then"          { fprintf(stderr, "[THEN]"); return THEN; }
"else"          { fprintf(stderr, "[ELSE]"); return ELSE; }
"while"         { fprintf(stderr, "[WHILE]"); return WHILE; }
"do"            { fprintf(stderr, "[DO]"); return DO; }


".."            { fprintf(stderr, "[DOTDOT]"); return DOTDOT; }

":="            { fprintf(stderr, "[ASSIGNOP]"); return ASSIGNOP; }

"="            { fprintf(stderr, "[RELOP: %d]", EQ); return RELOP; }
"<>"           { fprintf(stderr, "[RELOP: %d]", NE); return RELOP; }
"<"            { fprintf(stderr, "[RELOP: %d]", LT); return RELOP; }
"<="           { fprintf(stderr, "[RELOP: %d]", LE); return RELOP; }
">"            { fprintf(stderr, "[RELOP: %d]", GT); return RELOP; }
">="           { fprintf(stderr, "[RELOP: %d]", GE); return RELOP; }

"+"           { fprintf(stderr, "[ADDOP: %d]", PLUS); return ADDOP; }
"-"           { fprintf(stderr, "[ADDOP: %d]", MINUS); return ADDOP; }
"or"           { fprintf(stderr, "[ADDOP: %d]", OR); return ADDOP; }

"*"           { fprintf(stderr, "[MULOP: %d]", STAR); return MULOP; }
"/"           { fprintf(stderr, "[MULOP: %d]", SLASH); return MULOP; }
"and"         { fprintf(stderr, "[MULOP: %d]", AND); return MULOP; }

{number}                { fprintf(stderr, "[INUM:%d]", atoi(yytext)); return INUM; }
{number}"."{number}     { fprintf(stderr, "[RNUM:%f]", atof(yytext)); return RNUM; }
{ident}                 { fprintf(stderr, "[ID:%s]", yytext); return ID; }

";" { return yytext[0]; }
.   { fprintf(stderr, "{%c}", yytext[0]); return yytext[0]; }


%%

int yyerror (char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}