/* Page 746 Appendix A*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "y.tab.h"

extern char yychar;
extern int CURRENT_LINE_NUM;
#define DEBUG 0
%}

number [0-9]+
ident [A-Za-z][A-Za-z0-9]*
whitespace [ \t]+
comment1 \{[^{]*\}
comment2 \(\*.*\*\)     /* Should probably be fixed, includes anything between open and close */


%%
{whitespace}    ;
{comment1}       {/* fprintf(stderr, "%s", yytext); */ };
{comment2}       {/* fprintf(stderr, "%s", yytext); */ };

"program"       { if (DEBUG) fprintf(stderr, "[PROGRAM]");      return PROGRAM; }
"var"           { if (DEBUG) fprintf(stderr, "[VAR]");          return VAR; }
"array"         { if (DEBUG) fprintf(stderr, "[ARRAY]");        return ARRAY; }
"of"            { if (DEBUG) fprintf(stderr, "[OF]");           return OF; }
"procedure"     { if (DEBUG) fprintf(stderr, "[PROCEDURE]");    return PROCEDURE; }
"function"      { if (DEBUG) fprintf(stderr, "[FUNCTION]");     return FUNCTION; }
"begin"         { if (DEBUG) fprintf(stderr, "[BBEGIN]");       return BBEGIN; }
"end"           { if (DEBUG) fprintf(stderr, "[END]");          return END; }
"integer"       { if (DEBUG) fprintf(stderr, "[INTEGER]");      return INTEGER; }
"real"          { if (DEBUG) fprintf(stderr, "[REAL]");         return REAL; }
"if"            { if (DEBUG) fprintf(stderr, "[IF]");           return IF; }
"then"          { if (DEBUG) fprintf(stderr, "[THEN]");         return THEN; }
"else"          { if (DEBUG) fprintf(stderr, "[ELSE]");         return ELSE; }
"while"         { if (DEBUG) fprintf(stderr, "[WHILE]");        return WHILE; }
"for"           { if (DEBUG) fprintf(stderr, "[FOR]");          return FOR; }
"do"            { if (DEBUG) fprintf(stderr, "[DO]");           return DO; }
"to"            { if (DEBUG) fprintf(stderr, "[TO]");           return TO; }


"result"        { if (DEBUG) fprintf(stderr, "[RESULT]");      return RESULT; }
".."            { if (DEBUG) fprintf(stderr, "[DOTDOT]");      return DOTDOT; }

":="            { if (DEBUG) fprintf(stderr, "[ASSIGNOP]");            yylval.opval = ASSIGNOP; /* <-- Might not need this */ return ASSIGNOP; }

"="             { if (DEBUG) fprintf(stderr, "[RELOP: %d]", EQ);       yylval.opval = EQ; return RELOP; }
"<>"            { if (DEBUG) fprintf(stderr, "[RELOP: %d]", NE);       yylval.opval = NE; return RELOP; }
"<"             { if (DEBUG) fprintf(stderr, "[RELOP: %d]", LT);       yylval.opval = LT; return RELOP; }
"<="            { if (DEBUG) fprintf(stderr, "[RELOP: %d]", LE);       yylval.opval = LE; return RELOP; }
">"             { if (DEBUG) fprintf(stderr, "[RELOP: %d]", GT);       yylval.opval = GT; return RELOP; }
">="            { if (DEBUG) fprintf(stderr, "[RELOP: %d]", GE);       yylval.opval = GE; return RELOP; }
"not"           { if (DEBUG) fprintf(stderr, "[RELOP: %d]", NOT);       /* This is probably wrong */ yylval.opval = NOT; return RELOP; }

"+"             { if (DEBUG) fprintf(stderr, "[ADDOP: %d]", PLUS);     yylval.opval = PLUS;    return ADDOP; }
"-"             { if (DEBUG) fprintf(stderr, "[ADDOP: %d]", MINUS);    yylval.opval = MINUS;   return ADDOP; }
"or"            { if (DEBUG) fprintf(stderr, "[ADDOP: %d]", OR);       yylval.opval = OR;      return ADDOP; } 

"*"             { if (DEBUG) fprintf(stderr, "[MULOP: %d]", STAR);     yylval.opval = STAR;    return MULOP; }
"/"             { if (DEBUG) fprintf(stderr, "[MULOP: %d]", SLASH);    yylval.opval = SLASH;   return MULOP; }
"div"           { if (DEBUG) fprintf(stderr, "[MULOP: %d]", DIV);      yylval.opval = DIV;     return MULOP; }
"mod"           { if (DEBUG) fprintf(stderr, "[MULOP: %d]", MOD);      yylval.opval = MOD;     return MULOP; }
"and"           { if (DEBUG) fprintf(stderr, "[MULOP: %d]", AND);      yylval.opval = AND;     return MULOP; }

{number}                { if (DEBUG) fprintf(stderr, "[INUM:%d]", atoi(yytext)); yylval.ival = (int) atoi(yytext); return INUM; }
{number}"."{number}     { if (DEBUG) fprintf(stderr, "[RNUM:%f]", atof(yytext)); yylval.rval = (float) atof(yytext); return RNUM; }
{ident}                 { if (DEBUG) fprintf(stderr, "[ID:%s]", yytext); yylval.sval = strdup(yytext); return ID; }

";"                     { return yytext[0]; }
"\n"                    { if (DEBUG) fprintf(stderr, "\n"); CURRENT_LINE_NUM++; /* Add line counting here */ }
.                       { if (DEBUG) fprintf(stderr, "{%c}", yytext[0]); return yytext[0]; }


%%

int yyerror (char *msg) {
    fprintf(stderr, "\nError: %s\n", msg);
    // fprintf(stderr, "Error at string \"%s\"\n", yytext);
    exit(1);
}

// void debug_print(char *msg, int token) {
//     if (DEBUG) fprintf(stderr, );
// }