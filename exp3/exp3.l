%{
#include "wh.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%option noyywrap
%option nounput

%%
"while"                  { return WHILE; }
"("                      { return LPAREN; }
")"                      { return RPAREN; }
"{"                      { return LBRACE; }
"}"                      { return RBRACE; }
"="                      { return ASSIGN; }
"<"                      { return LT; }
">"                      { return GT; }
"=="                     { return EQ; }
"+"                      { return PLUS; }
"-"                      { return MINUS; }
"*"                      { return MULT; }
"/"                      { return DIV; }
";"                      { return ';'; } /* semicolon as literal */
[0-9]+                    { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]*      { return IDENTIFIER; }
[ \t\n]+                 { /* skip whitespace */ }
.                         { printf("Unexpected character: %s\n", yytext); return yytext[0]; }
<<EOF>>                   { return 0; }
%%
