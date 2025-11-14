%{
#include "calc.tab.h" // Include the parser's header for token definitions
#include <stdio.h>
#include <stdlib.h>
%}

%option noyywrap

%%
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[ \t]+         { /* Ignore whitespace */ }
"+"            { return PLUS; }
"-"            { return MINUS; }
"*"            { return MULT; }
"/"            { return DIV; }
"("            { return LPAREN; }
")"            { return RPAREN; }
\n              { return '\n'; } /* Recognize newline as a token */
.               { printf("Unexpected character: %s\n", yytext); }
%%
