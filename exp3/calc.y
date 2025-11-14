%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex();
%}

%token NUMBER
%token PLUS MINUS MULT DIV LPAREN RPAREN
%left PLUS MINUS
%left MULT DIV
%%
input:
    /* empty */
  | input line
;

line:
    '\n'
  | expression '\n' { printf("Result: %d\n", $1); }
;

expression:
    NUMBER                { $$ = $1; }
  | expression PLUS expression   { $$ = $1 + $3; }
  | expression MINUS expression  { $$ = $1 - $3; }
  | expression MULT expression   { $$ = $1 * $3; }
  | expression DIV expression    { $$ = $1 / $3; }
  | LPAREN expression RPAREN     { $$ = $2; }
;
%%

int main(void) {
    printf("Enter expressions to calculate (Ctrl+C to exit):\n");
    yyparse();
    return 0;
}
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
