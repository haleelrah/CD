%{
#include <stdio.h>
#include "Validarith.tab.h"
%}
%%
[a-zA-Z]+ { return VARIABLE; }
[0-9]+
{ return NUMBER; }
[\t ];
/* ignore tabs and spaces */
\n{ return 0; } /* end of input */
.{ return yytext[0]; }
%%
int yywrap(void) {
return 1;
}
%{
#include <stdio.h>
#include <stdlib.h>
// Function prototypes
int yylex(void);
void yyerror(const char *s);%}
%token NUMBER VARIABLE
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS
%%
S: E {
printf("\nEntered arithmetic expression is valid\n\n");
}
;
E: E '+' E
| E '-' E
| E '*' E
| E '/' E
| E '%' E
| '-' E %prec UMINUS /* handle unary minus */
| '(' E ')'
| NUMBER
| VARIABLE
;
%%
int main(void) {
printf("\nEnter any arithmetic expression:\n");
yyparse();
return 0;
}
void yyerror(const char *s) {
printf("\nEntered arithmetic expression is invalid: %s\n\n", s);
}

