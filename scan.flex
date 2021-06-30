%option noyywrap
 
%{
#include <stdio.h>
#include <string.h>
#include "parse.tab.h"
extern int yylex();
%}
 
%%
 


"LEFT"	{yylval.val = 1; return DIR;}
"RIGHT" {yylval.val = 2; return DIR;}
"UP"	{yylval.val = 3; return DIR;}
"DOWN" {yylval.val = 4; return DIR;}

"ADD"	{yylval.val = 1; return OP;}
"SUBTRACT"	{yylval.val = 2; return OP;}
"MULTIPLY"	{yylval.val = 3; return OP;}
"DIVIDE"	{yylval.val = 4; return OP;}

"ASSIGN" { return ASSIGN;}
[0-9]+ {yylval.val = atoi(yytext); return NUMBER;}
"TO" {return TO;}

"VALUE" { return VALUE;}
"IN" {return IN;}

"IS" {return IS;}
"VAR" { return VAR;}
[a-zA-Z][a-zA-Z]* {strcpy(yylval.id,yytext); return VARNAME;}//variable name.

\, {return COMMA;}
\. {return PERIOD;}
\n 	{return EOL;}

[ \t]+	;//Ignore spaces

[^ \n\,\.]+ { return INVALID;}//Token for invalid variable names.
 
%%
 
 