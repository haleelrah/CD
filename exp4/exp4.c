%{
#include "tac.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}
%%
[0-9]+
{ yylval.symbol = atoi(yytext); return NUMBER; }
[a-zA-Z] { yylval.symbol = yytext[0]; return LETTER; }
"+"
{ return '+'; }
"-"
{ return '-'; }
"*"
{ return '*'; }
"/"
{ return '/'; }
"="
{ return '='; }
";"
{ return ';'; }
"("
{ return '('; }
")"
{ return ')'; }
[ \t\n] { /* skip whitespace */ }
.
{ printf("Unexpected character: %s\n", yytext); }
%%
int yywrap() {
return 1; // Indicate no more input}
Yacc program(tac.y):
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void); // Declaration of yylex
struct expr {
char operand1;
char operand2;
char operator;
char result;
};
char addtotable(char a, char b, char o);
void threeAdd();
void yyerror(const char *s);
// Global variables
struct expr arr[20];
int index1 = 0;
char temp = 'A' - 1;
%}
%union {
char symbol;
}
%left '+' '-'
%left '*' '/'
%token <symbol> LETTER NUMBER
%type <symbol> exp
%%
// Grammar rules
statement:
LETTER '=' exp ';' { addtotable($1, $3, '='); }
;
exp:
exp '+' exp { $$ = addtotable($1, $3, '+'); }
| exp '-' exp { $$ = addtotable($1, $3, '-'); }
| exp '*' exp { $$ = addtotable($1, $3, '*'); }
| exp '/' exp { $$ = addtotable($1, $3, '/'); }
| '(' exp ')' { $$ = $2; }
| NUMBER { $$ = $1; }
| LETTER { $$ = $1; }
;
%%
// Error handling function
void yyerror(const char *s) {
fprintf(stderr, "Error: %s\n", s);
}
// Function to add a record to the table

char addtotable(char a, char b, char o) {
temp++;
arr[index1].operand1 = a;
arr[index1].operand2 = b;
arr[index1].operator = o;
arr[index1].result = temp;
index1++;
return temp;
}
// Function to display the three-address code
void threeAdd() {
for (int i = 0; i < index1; i++) {
printf("%c := %c %c %c\n", arr[i].result, arr[i].operand1, arr[i].operator, arr[i].operand2);
}
}
// Main function
int main() {
printf("Enter the expression: ");
yyparse();
threeAdd();
return 0;
}