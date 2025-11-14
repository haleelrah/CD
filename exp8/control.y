%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex(void);
int yydebug = 1; /* enable parser debug traces */
void yyerror(const char *s) { fprintf(stderr, "Parse error: %s\n", s); }
%}

%union {
  int ival;
  char *string;
}

%token <string> ID
%token <ival> NUMBER
%token IF ELSE WHILE FOR SWITCH CASE DEFAULT BREAK
%token EQ NE LT GT LE GE
%token PLUS MINUS MULT DIV ASSIGN
%token LPAREN RPAREN LBRACE RBRACE COLON COMMA SEMI

%left PLUS MINUS
%left MULT DIV

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
program:
    /* empty */
  | program external
;

external:
    statement
  | ';'
;

statement:
    compound_statement
  | expression_stmt
  | selection_statement
  | iteration_statement
  | jump_statement
;

compound_statement:
    LBRACE program RBRACE
;

expression_stmt:
    SEMI
  | expression SEMI
;

selection_statement:
    IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
  | IF LPAREN expression RPAREN statement ELSE statement
  | SWITCH LPAREN expression RPAREN LBRACE switch_body RBRACE
;

switch_body:
    /* empty */
  | switch_body switch_case
;

switch_case:
    CASE NUMBER COLON program
  | DEFAULT COLON program
;

iteration_statement:
    WHILE LPAREN expression RPAREN statement
  | FOR LPAREN for_init for_cond for_iter RPAREN statement
;

for_init:
    SEMI
  | expression SEMI
;

for_cond:
    /* empty */
  | expression SEMI
;

for_iter:
    /* empty */
  | expression
;

jump_statement:
    BREAK SEMI
;

expression:
    assignment_expression
;

assignment_expression:
    logical_or_expression
  | ID ASSIGN assignment_expression
;

logical_or_expression:
    logical_and_expression
  | logical_or_expression '|' logical_and_expression
;

logical_and_expression:
    equality_expression
  | logical_and_expression '&' equality_expression
;

equality_expression:
    relational_expression
  | equality_expression EQ relational_expression
  | equality_expression NE relational_expression
;

relational_expression:
    additive_expression
  | relational_expression LT additive_expression
  | relational_expression GT additive_expression
  | relational_expression LE additive_expression
  | relational_expression GE additive_expression
;

additive_expression:
    multiplicative_expression
  | additive_expression PLUS multiplicative_expression
  | additive_expression MINUS multiplicative_expression
;

multiplicative_expression:
    primary_expression
  | multiplicative_expression MULT primary_expression
  | multiplicative_expression DIV primary_expression
;

primary_expression:
    ID
  | NUMBER
  | LPAREN expression RPAREN
;

%%

int main(void) {
    printf("Enter control-structure snippets (Ctrl+D to finish):\n");
    if (yyparse() == 0) printf("Input parsed successfully.\n");
    return 0;
}
