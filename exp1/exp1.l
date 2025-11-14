%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SYMBOLS 100
struct SymbolTable { char name[100]; } symtab[MAX_SYMBOLS];
int symcount = 0;
int search(char *name) {
    for (int i = 0; i < symcount; i++) {
        if (strcmp(symtab[i].name, name) == 0)
            return 1;
    }
    return 0;
}
void add(char *name) {
    if (!search(name)) {
        strcpy(symtab[symcount].name, name);
        symcount++;
    }
}
%}
%%
[ \t\n]+                       { /* skip whitespace */ }
"//".*                         { printf("Comment: %s\n", yytext); }
"/*"([^*]|\*+[^*/])*\*+\/    { printf("Multiline Comment: %s\n", yytext); }
[0-9]+                          { printf("Constant: %s\n", yytext); }
"=="|"!="|"<="|">="|"="|"+"|"-"|"*"|"/"  { printf("Operator: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*          { printf("Identifier: %s\n", yytext); add(yytext); }
[;:{}()<>\[\]]                { printf("Punctuation: %s\n", yytext); }
.                               { printf("Unknown token: %s\n", yytext); }
%%

int main(int argc, char **argv) {
    printf("Lexical Analysis Started:\n");
    yylex();
    printf("\nSymbol Table:\n");
    for (int i = 0; i < symcount; i++) {
        printf("%d: %s\n", i+1, symtab[i].name);
    }
    return 0;
}

int yywrap() { return 1; }
