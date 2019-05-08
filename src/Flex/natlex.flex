%option noyywrap

/* http://web.mit.edu/gnu/doc/html/flex_1.html */

/* Imports */
%{
/* atof */
#include <math.h>
%}

    int tokens = 0, lines = 0;

DIGIT       [0-9]
ID          [a-zA-Z][a-zA-Z0-9_]*
TYPE        (int)|(float)|(bool)|(list)|(array)
CONST       (null)|(inf)|(true)|(false)
CONTROL     (loop)|(until)|(where)|(while)|(for)|(if)|(continue)|(break)|(in)|(is)|(of)|(with)
OBJECT      (object)|(idea)|(this)|(from)
STRING      \"(\\.|[^"\\])*\"
SEPERATOR   [,\.\(\)\[\]{}']
OPERATOR    "+"|"-"|"*"|"/"|"%"|"="|"+="|"-="|"*="|"/="|"%="|">>"|"<<"|(and)|(or)|(xor)|(nand)|(nor)|(not)|(xnor)
TAB         [\t]|"    "
SPACE       [ ]
NEWLINE     [\n]

/* Rules */
%%
{DIGIT}+    {
    printf("Int('%d') ", atoi(yytext));
    ++tokens;
}
{TYPE}  {
    printf("Type('%s') ", yytext);
    ++tokens;
}
{CONST} {
    printf("Const('%s') ", yytext);
    ++tokens;
}
{CONTROL}   {
    printf("Ctrl('%s') ", yytext);
    ++tokens;
}
{OBJECT}    {
    printf("Obj('%s') ", yytext);
    ++tokens;
}
{STRING}    {
    printf("Str(%s) ", yytext);
    ++tokens;
}
{SEPERATOR} {
    printf("Sep('%s') ", yytext);
    ++tokens;
}
{OPERATOR}  {
    printf("Op('%s') ", yytext);
    ++tokens;
}
{TAB}   {
    printf("Tab ");
    ++tokens;
}
{SPACE} {
    ++tokens;
}
{NEWLINE}   {
    ++tokens;
    ++lines;
    printf("\n");
}
{ID}    {
    printf("ID('%s') ", yytext);
    ++tokens;
}
%%

main(argc, argv)
int argc;
char **argv;
{
    ++argv, --argc; /* skip over program name */
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

    yylex();
    printf("\nToken count: %d Line count: %d\n", tokens, lines);
}
