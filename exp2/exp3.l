%{
#include "valid_identifier.tab.h"
%}
%%
[a-zA-Z][a-zA-Z0-9]*    { return IDENTIFIER; }
[ \t]+                  { /* skip spaces */ }
\n                      { return 0; } /* end of input */
.                       { return yytext[0]; } /* other chars -- return as token to trigger parse error */
%%

int yywrap(void) { return 1; }
