%{
#include <stdio.h>
#include <ctype.h>
/* Declaration of yylex and yyerror */
int yylex(void);
int yyerror(const char *s);
%}
%token IDENTIFIER
%%
start:
    IDENTIFIER { printf("It is a valid identifier!\n"); }
  | error      { yyerror("invalid identifier"); }
;
%%
int yyerror(const char *s) {
    printf("It is not a valid identifier!\n");
    return 0;
}

int main() {
    printf("Enter a name to be tested for identifier: ");
    yyparse();
    return 0;
}
