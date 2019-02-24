/* Page 746 Appendix A*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "y.tab.h"

extern char yychar;
%}

number [0-9]+
ident [A-Za-z][A-Za-z0-9]*
whitespace [ \t]+
comment \{[^{]*\}


%%
{whitespace}    ;
{comment}       ;

"program"       { fprintf(stderr, "[PROGRAM]");     return PROGRAM; }
"var"           { fprintf(stderr, "[VAR]");         return VAR; }
"array"         { fprintf(stderr, "[ARRAY]");       return ARRAY; }
"of"            { fprintf(stderr, "[OF]");          return OF; }
"procedure"     { fprintf(stderr, "[PROCEDURE]");   return PROCEDURE; }
"function"      { fprintf(stderr, "[FUNCTION]");    return FUNCTION; }
"begin"         { fprintf(stderr, "[BBEGIN]");      return BBEGIN; }
"end"           { fprintf(stderr, "[END]");         return END; }
"integer"       { fprintf(stderr, "[INTEGER]");     return INTEGER; }
"real"          { fprintf(stderr, "[REAL]");        return REAL; }
"if"            { fprintf(stderr, "[IF]");          return IF; }
"then"          { fprintf(stderr, "[THEN]");        return THEN; }
"else"          { fprintf(stderr, "[ELSE]");        return ELSE; }
"while"         { fprintf(stderr, "[WHILE]");       return WHILE; }
"do"            { fprintf(stderr, "[DO]");          return DO; }

"result"        { fprintf(stderr, "[RESULT]");      return RESULT; }
".."            { fprintf(stderr, "[DOTDOT]");      return DOTDOT; }

":="            { fprintf(stderr, "[ASSIGNOP]");            yylval.opval = ASSIGNOP; return ASSIGNOP; }

"="             { fprintf(stderr, "[RELOP: %d]", EQ);       yylval.opval = EQ; return RELOP; }
"<>"            { fprintf(stderr, "[RELOP: %d]", NE);       yylval.opval = NE; return RELOP; }
"<"             { fprintf(stderr, "[RELOP: %d]", LT);       yylval.opval = LT; return RELOP; }
"<="            { fprintf(stderr, "[RELOP: %d]", LE);       yylval.opval = LE; return RELOP; }
">"             { fprintf(stderr, "[RELOP: %d]", GT);       yylval.opval = GT; return RELOP; }
">="            { fprintf(stderr, "[RELOP: %d]", GE);       yylval.opval = GE; return RELOP; }
"not"           { fprintf(stderr, "[RELOP: %d]", NOT);       yylval.opval = NOT; return RELOP; }

"+"             { fprintf(stderr, "[ADDOP: %d]", PLUS);     yylval.opval = PLUS;    return ADDOP; }
"-"             { fprintf(stderr, "[ADDOP: %d]", MINUS);    yylval.opval = MINUS;   return ADDOP; }
"or"            { fprintf(stderr, "[ADDOP: %d]", OR);       yylval.opval = OR;      return ADDOP; } 

"*"             { fprintf(stderr, "[MULOP: %d]", STAR);     yylval.opval = STAR;    return MULOP; }
"/"             { fprintf(stderr, "[MULOP: %d]", SLASH);    yylval.opval = SLASH;   return MULOP; }
"div"           { fprintf(stderr, "[MULOP: %d]", DIV);      yylval.opval = DIV;     return MULOP; }
"mod"           { fprintf(stderr, "[MULOP: %d]", MOD);      yylval.opval = MOD;     return MULOP; }
"and"           { fprintf(stderr, "[MULOP: %d]", AND);      yylval.opval = AND;     return MULOP; }

{number}                { fprintf(stderr, "[INUM:%d]", atoi(yytext)); yylval.ival = (int) atoi(yytext); return INUM; }
{number}"."{number}     { fprintf(stderr, "[RNUM:%f]", atof(yytext)); yylval.rval = (float) atof(yytext); return RNUM; }
{ident}                 { fprintf(stderr, "[ID:%s]", yytext); yylval.sval = yytext; return ID; }

";" { return yytext[0]; }
.   { fprintf(stderr, "{%c}", yytext[0]); return yytext[0]; }


%%

int yyerror (char *msg) {
    fprintf(stderr, "\nError: %s\n", msg);
    fprintf(stderr, "Error at string <%s>\n", yytext);
    exit(1);
}