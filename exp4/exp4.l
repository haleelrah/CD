%{
#include "tac.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%option noyywrap

%%
[0-9]+          { yylval.symbol = (char)atoi(yytext); return NUMBER; }
[a-zA-Z]       { yylval.symbol = yytext[0]; return LETTER; }
"+"            { return '+'; }
"-"            { return '-'; }
"*"            { return '*'; }
"/"            { return '/'; }
"="            { return '='; }
";"            { return ';'; }
"("            { return '('; }
")"            { return ')'; }
[ \t\n]        { /* skip whitespace */ }
.               { printf("Unexpected character: %s\n", yytext); }
%%
