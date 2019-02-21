#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "pc.y"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "y.tab.h"

extern int yyerror(char*);
extern int yylex();
#line 11 "pc.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
    int ival;   /* INUM */
    float rval; /* RNUM */
    int opval;  /* RELOP ADDOP MULOP */
    char *sval; /* ID */
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 41 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define PROGRAM 257
#define BBEGIN 258
#define END 259
#define VAR 260
#define PROCEDURE 261
#define FUNCTION 262
#define ARRAY 263
#define OF 264
#define INTEGER 265
#define REAL 266
#define IF 267
#define THEN 268
#define ELSE 269
#define WHILE 270
#define DO 271
#define ASSIGNOP 272
#define RELOP 273
#define EQ 274
#define NE 275
#define LT 276
#define LE 277
#define GT 278
#define GE 279
#define ADDOP 280
#define PLUS 281
#define MINUS 282
#define OR 283
#define MULOP 284
#define STAR 285
#define SLASH 286
#define AND 287
#define NOT 288
#define DOTDOT 289
#define ID 290
#define INUM 291
#define RNUM 292
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    5,    5,    6,    6,    3,
    3,    7,    8,    8,    9,    9,   10,   10,    4,   11,
   11,   12,   12,   13,   13,   13,   13,   13,   14,   14,
   16,   16,   17,   17,   15,   15,   18,   18,   18,   19,
   19,   21,   21,   21,   21,   21,   21,   21,   20,   20,
};
static const short yylen[] = {                            2,
   10,    1,    3,    6,    0,    1,    8,    1,    1,    3,
    0,    4,    6,    4,    3,    0,    3,    5,    3,    1,
    0,    1,    3,    3,    1,    1,    6,    4,    1,    4,
    1,    4,    1,    3,    1,    3,    1,    2,    3,    1,
    3,    1,    4,    4,    1,    1,    3,    2,    1,    1,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    2,    0,    0,    0,    5,    3,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    5,
    0,    0,    0,    0,   26,    0,    0,   22,    0,   25,
    0,    0,    1,   10,    0,    0,    8,    9,    0,    6,
    0,    0,   45,   46,    0,   49,   50,    0,    0,    0,
    0,   40,    0,    0,    0,   19,    0,    0,    0,    0,
    0,    0,    0,    4,   48,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   33,    0,    0,   23,   24,    0,
    0,   14,    0,   12,    0,    0,    0,   47,    0,    0,
    0,   41,   28,   32,    0,   30,    0,   15,    0,    0,
    0,   44,   43,    0,   34,   17,    0,   13,    0,   27,
    0,    0,   18,    0,    7,
};
static const short yydgoto[] = {                          2,
    6,   11,   13,   25,   39,   40,   19,   20,   60,   81,
   26,   27,   28,   29,   75,   30,   76,   49,   50,   51,
   52,
};
static const short yysindex[] = {                      -242,
 -269,    0,  -17, -246,    0,   38,    7, -206,    0,    0,
 -183, -246, -188,  -27, -240, -204, -199,   48,   37,    0,
 -185,  -40,  -40,  -32,    0, -162,   39,    0, -173,    0,
   60,   60,    0,    0, -183,   11,    0,    0,   42,    0,
  -34,  -28,    0,    0,  -40,    0,    0, -164, -213, -179,
  -34,    0, -165,  -40,  -40,    0, -240,  -40, -246,   50,
   52, -188, -184,    0,    0,  -40,  -40,   67, -240,  -40,
  -34,  -34, -179, -240,    0,   44,   18,    0,    0,  -19,
  -30,    0, -233,    0, -177,   49,   20,    0, -155, -161,
 -179,    0,    0,    0,  -40,    0, -185,    0, -246,   56,
 -175,    0,    0, -240,    0,    0,  -18,    0,   25,    0,
 -185, -144,    0, -233,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -186,    0,    0,    0, -138,    0,    0,    0,    0,    0,
    0,    0,    0,  -58,    0,    0, -137,    0,    0,    0,
   64,   66,    0,    0, -186,    0,    0,    0,    0,    0,
    0,  -37,    0,    0,    0,    0,    0,    0,   10,  -31,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   -6,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   24,
    2,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
  -10,  105,   91,   -4,  -63,  -69,    0,    0,   95,    0,
    0,    0,  -33,    0,   -3,    0,   62,   59,  -14,    0,
  -25,
};
#define YYTABLESIZE 295
static const short yytable[] = {                         45,
   31,   14,   46,   42,   47,   45,   42,   54,   18,   37,
   98,   66,   37,  100,    1,   65,    8,   15,   48,   53,
    3,   42,    4,   78,    8,    8,   22,   37,   99,   23,
   21,   37,   38,  106,   38,   89,   73,   38,   97,  111,
   93,   68,   39,    5,  115,   39,   92,  113,   80,   24,
   35,   77,   38,   35,   79,   42,   91,   84,   55,   70,
   39,   37,   67,   87,   36,    9,   71,   36,   35,   15,
  110,   11,   16,   17,   11,   11,   12,   36,    7,   37,
   38,    8,   36,   10,   94,   31,   38,   95,  107,  102,
   32,  105,   95,   33,   39,   34,   56,   57,   58,   59,
   64,   63,   35,   69,   72,   74,   85,   88,   82,   83,
   96,  101,  103,  104,  108,  109,   36,  112,   71,  114,
   21,   20,   16,   16,   35,   62,   61,   86,   90,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   31,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   31,    0,    0,   29,    0,    0,    0,    0,    0,    0,
    0,   42,    0,    0,    0,    0,    0,   37,    0,    0,
   42,   42,    0,   42,    0,   42,   37,   37,    0,   37,
    0,   37,   42,    0,    0,    0,   42,   41,   37,   42,
   43,   44,   38,   41,    0,   42,   43,   44,    0,    0,
   39,   38,   38,    0,   38,    0,   38,    0,   35,   39,
   39,    0,   39,   38,   39,    0,    0,   35,   35,    0,
   35,   39,   36,    0,    0,    0,    0,    0,    0,    0,
    0,   36,   36,    0,   36,
};
static const short yycheck[] = {                         40,
   59,   12,   43,   41,   45,   40,   44,   40,   13,   41,
   41,   40,   44,   83,  257,   41,   44,  258,   22,   23,
  290,   59,   40,   57,   44,   44,  267,   59,   59,  270,
   58,  265,  266,   97,   41,   69,   51,   44,   58,   58,
   74,   45,   41,  290,  114,   44,   72,  111,   59,  290,
   41,   55,   59,   44,   58,   93,   71,   62,   91,  273,
   59,   93,   91,   67,   41,   59,  280,   44,   59,  258,
  104,  258,  261,  262,  261,  262,  260,  263,   41,  265,
  266,   44,   59,  290,   41,  290,   93,   44,   99,   41,
  290,   95,   44,   46,   93,   59,  259,   59,  272,   40,
   59,   91,   93,  268,  284,  271,  291,   41,   59,   58,
   93,  289,   93,  269,   59,  291,   93,   93,  280,  264,
  259,  259,   59,   58,   20,   35,   32,   66,   70,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  259,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  269,   -1,   -1,  272,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  259,   -1,   -1,   -1,   -1,   -1,  259,   -1,   -1,
  268,  269,   -1,  271,   -1,  273,  268,  269,   -1,  271,
   -1,  273,  280,   -1,   -1,   -1,  284,  288,  280,  290,
  291,  292,  259,  288,   -1,  290,  291,  292,   -1,   -1,
  259,  268,  269,   -1,  271,   -1,  273,   -1,  259,  268,
  269,   -1,  271,  280,  273,   -1,   -1,  268,  269,   -1,
  271,  280,  259,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  268,  269,   -1,  271,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 292
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,"'+'","','","'-'","'.'",0,0,0,0,0,0,0,0,0,0,0,"':'",
"';'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,
"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"PROGRAM","BBEGIN","END","VAR","PROCEDURE","FUNCTION","ARRAY","OF",
"INTEGER","REAL","IF","THEN","ELSE","WHILE","DO","ASSIGNOP","RELOP","EQ","NE",
"LT","LE","GT","GE","ADDOP","PLUS","MINUS","OR","MULOP","STAR","SLASH","AND",
"NOT","DOTDOT","ID","INUM","RNUM",
};
static const char *yyrule[] = {
"$accept : program",
"program : PROGRAM ID '(' identifier_list ')' ';' declarations subprogram_declarations compound_statement '.'",
"identifier_list : ID",
"identifier_list : identifier_list ',' ID",
"declarations : declarations VAR identifier_list ':' type ';'",
"declarations :",
"type : standard_type",
"type : ARRAY '[' INUM DOTDOT INUM ']' OF standard_type",
"standard_type : INTEGER",
"standard_type : REAL",
"subprogram_declarations : subprogram_declarations subprogram_declaration ';'",
"subprogram_declarations :",
"subprogram_declaration : subprogram_head declarations subprogram_declarations compound_statement",
"subprogram_head : FUNCTION ID arguments ':' standard_type ';'",
"subprogram_head : PROCEDURE ID arguments ';'",
"arguments : '(' parameter_list ')'",
"arguments :",
"parameter_list : identifier_list ':' type",
"parameter_list : parameter_list ';' identifier_list ':' type",
"compound_statement : BBEGIN optional_statements END",
"optional_statements : statement_list",
"optional_statements :",
"statement_list : statement",
"statement_list : statement_list ';' statement",
"statement : variable ASSIGNOP expression",
"statement : procedure_statement",
"statement : compound_statement",
"statement : IF expression THEN statement ELSE statement",
"statement : WHILE expression DO statement",
"variable : ID",
"variable : ID '[' expression ']'",
"procedure_statement : ID",
"procedure_statement : ID '(' expression_list ')'",
"expression_list : expression",
"expression_list : expression_list ',' expression",
"expression : simple_expression",
"expression : simple_expression RELOP simple_expression",
"simple_expression : term",
"simple_expression : sign term",
"simple_expression : simple_expression ADDOP term",
"term : factor",
"term : term MULOP factor",
"factor : ID",
"factor : ID '[' expression ']'",
"factor : ID '(' expression_list ')'",
"factor : INUM",
"factor : RNUM",
"factor : '(' expression ')'",
"factor : NOT factor",
"sign : '+'",
"sign : '-'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
