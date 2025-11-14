#include <stdio.h>
#include <string.h>

int main(void) {
    char icode[10][30];
    char str[30];
    char opr[10];
    int i = 0;

    printf("\nEnter the set of intermediate code (terminated by exit):\n");
    while (i < 10 && scanf(" %29s", icode[i]) == 1) {
        if (strcmp(icode[i], "exit") == 0) break;
        i++;
    }

    int count = i;
    printf("\nTarget code generation\n");
    printf("************************\n");

    for (i = 0; i < count; i++) {
        strncpy(str, icode[i], sizeof(str) - 1);
        str[sizeof(str) - 1] = '\0';

        char op = (strlen(str) > 3) ? str[3] : '\0';
        switch (op) {
        case '+': strcpy(opr, "ADD"); break;
        case '-': strcpy(opr, "SUB"); break;
        case '*': strcpy(opr, "MUL"); break;
        case '/': strcpy(opr, "DIV"); break;
        default: strcpy(opr, "UNK"); break;
        }

        /* Expecting a format like a=b+c */
        char dest = (strlen(str) > 0) ? str[0] : '\0';
        char src1 = (strlen(str) > 2) ? str[2] : '\0';
        char src2 = (strlen(str) > 4) ? str[4] : '\0';

        printf("\n\tMov %c, R%d", src1, i);
        printf("\n\t%s %c, R%d", opr, src2, i);
        printf("\n\tMov R%d, %c\n", i, dest);
    }

    return 0;
}