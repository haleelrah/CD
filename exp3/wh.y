%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
int yylex(void);
%}

/* Define tokens */
%token WHILE LPAREN RPAREN LBRACE RBRACE SEMICOLON IDENTIFIER NUMBER
%token ASSIGN LT GT EQ PLUS MINUS MULT DIV

%left PLUS MINUS
%left MULT DIV
%left LT GT EQ
%right ASSIGN

%%
program:
    statement
;

statement:
    WHILE LPAREN condition RPAREN LBRACE statements RBRACE
    {
        printf("Valid 'while' loop recognized.\n");
    }
  | assignment ';'
  | IDENTIFIER
  | NUMBER
;

statements:
    /* empty */
  | statements statement
;

assignment:
    IDENTIFIER ASSIGN expression
;

condition:
    expression LT expression
  | expression GT expression
  | expression EQ expression
;

expression:
    IDENTIFIER
  | NUMBER
  | expression PLUS expression
  | expression MINUS expression
  | expression MULT expression
  | expression DIV expression
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter a 'while' loop to check:\n");
    yyparse();
    return 0;
}
