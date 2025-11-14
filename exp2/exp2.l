%{
#include <stdio.h>
#include "Validarith.tab.h"
%}
%%
[a-zA-Z]+      { return VARIABLE; }
[0-9]+         { return NUMBER; }
[\t ]+        { /* ignore tabs and spaces */ }
\n             { return 0; } /* end of input */
.               { return yytext[0]; }
%%
int yywrap(void) { return 1; }
