%{
#include "control.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%option noyywrap

DIGIT  [0-9]
ID     [a-zA-Z_][a-zA-Z0-9_]*

%%
"//".*                  { /* skip single-line comments */ }
"/\*"([^*]|\*+[^*/])*\*+\/(\r?\n)?   { /* skip C comments */ }
[ \t\r\n]+            { /* skip whitespace */ }
"if"\b                 { return IF; }
"else"\b               { return ELSE; }
"while"\b              { return WHILE; }
"for"\b                { return FOR; }
"switch"\b             { return SWITCH; }
"case"\b               { return CASE; }
"default"\b            { return DEFAULT; }
"break"\b              { return BREAK; }
{ID}                    { yylval.string = strdup(yytext); return ID; }
{DIGIT}+                { yylval.ival = atoi(yytext); return NUMBER; }
"=="                   { return EQ; }
"!="                   { return NE; }
"<="                   { return LE; }
">="                   { return GE; }
"<"                    { return LT; }
">"                    { return GT; }
"+"                    { return PLUS; }
"-"                    { return MINUS; }
"*"                    { return MULT; }
"/"                    { return DIV; }
"("                    { return LPAREN; }
")"                    { return RPAREN; }
"{"                    { return LBRACE; }
"}"                    { return RBRACE; }
":"                    { return COLON; }
","                    { return COMMA; }
";"                    { return SEMI; }
"="                    { return ASSIGN; }
.                       { /* any other character */ return yytext[0]; }
%%

/* yywrap is disabled by %option noyywrap */
