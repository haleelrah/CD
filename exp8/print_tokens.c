#include <stdio.h>
#include "control.tab.h"

extern int yylex(void);
extern YYSTYPE yylval;
/* define yylval here so we can link against lex.yy.c without control.tab.c */
YYSTYPE yylval;

int main(void) {
    int t;
    while ((t = yylex()) != 0) {
        switch (t) {
            case IF: printf("IF\n"); break;
            case ELSE: printf("ELSE\n"); break;
            case WHILE: printf("WHILE\n"); break;
            case FOR: printf("FOR\n"); break;
            case SWITCH: printf("SWITCH\n"); break;
            case CASE: printf("CASE\n"); break;
            case DEFAULT: printf("DEFAULT\n"); break;
            case BREAK: printf("BREAK\n"); break;
            case ID: printf("ID(%s)\n", yylval.string); break;
            case NUMBER: printf("NUMBER(%d)\n", yylval.ival); break;
            case LPAREN: printf("LPAREN\n"); break;
            case RPAREN: printf("RPAREN\n"); break;
            case LBRACE: printf("LBRACE\n"); break;
            case RBRACE: printf("RBRACE\n"); break;
            case SEMI: printf("SEMI\n"); break;
            case ASSIGN: printf("ASSIGN\n"); break;
            case LT: printf("LT\n"); break;
            case GT: printf("GT\n"); break;
            case EQ: printf("EQ\n"); break;
            case PLUS: printf("PLUS\n"); break;
            default:
                printf("CHAR(%c) token=%d\n", t, t);
        }
    }
    return 0;
}
