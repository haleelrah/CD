%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
struct expr {
    char operand1;
    char operand2;
    char operator;
    char result;
};
char addtotable(char a, char b, char o);
void threeAdd();
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

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

char addtotable(char a, char b, char o) {
    temp++;
    arr[index1].operand1 = a;
    arr[index1].operand2 = b;
    arr[index1].operator = o;
    arr[index1].result = temp;
    index1++;
    return temp;
}

void threeAdd() {
    for (int i = 0; i < index1; i++) {
        printf("%c := %c %c %c\n", arr[i].result, arr[i].operand1, arr[i].operator, arr[i].operand2);
    }
}

int main() {
    printf("Enter the expression: \n");
    yyparse();
    threeAdd();
    return 0;
}
