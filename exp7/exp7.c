#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Helper to find operator position in RHS */
int find_operator(const char *rhs) {
    for (int i = 0; rhs[i]; i++) {
        if (rhs[i] == '+' || rhs[i] == '-' || rhs[i] == '*' || rhs[i] == '/') {
            return i;
        }
    }
    return -1;
}

int main(void) {
    char icode[10][30];
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
        char *line = icode[i];

        /* Split by '=' to get left and right parts */
        char *eq_pos = strchr(line, '=');
        if (!eq_pos) {
            fprintf(stderr, "Invalid format: %s (expected format: src1 op src2 = dest or dest = src1 op src2)\n", line);
            continue;
        }

        /* Extract left and right parts */
        char left[30], right[30];
        int left_len = (int)(eq_pos - line);
        if (left_len >= (int)sizeof(left)) left_len = sizeof(left) - 1;
        strncpy(left, line, left_len);
        left[left_len] = '\0';

        /* Trim trailing spaces from left */
        while (left_len > 0 && isspace(left[left_len - 1])) {
            left[--left_len] = '\0';
        }

        /* Extract right part (after '=') */
        const char *right_ptr = eq_pos + 1;
        while (*right_ptr && isspace(*right_ptr)) right_ptr++;
        strncpy(right, right_ptr, sizeof(right) - 1);
        right[sizeof(right) - 1] = '\0';
        int right_len = (int)strlen(right);
        while (right_len > 0 && isspace(right[right_len - 1])) {
            right[--right_len] = '\0';
        }

        /* Determine format: left has operator → (src1 op src2 = dest), else (dest = src1 op src2) */
        int op_pos_left = find_operator(left);
        int op_pos_right = find_operator(right);

        char dest[30], src1[30], src2[30];
        char opr[10];
        char op;

        if (op_pos_left >= 0) {
            /* Format: src1 op src2 = dest */
            strcpy(dest, right);
            /* Extract src1 and src2 from left */
            strncpy(src1, left, op_pos_left);
            src1[op_pos_left] = '\0';
            int src1_len = (int)strlen(src1);
            while (src1_len > 0 && isspace(src1[src1_len - 1])) {
                src1[--src1_len] = '\0';
            }

            op = left[op_pos_left];
            const char *src2_start = left + op_pos_left + 1;
            while (*src2_start && isspace(*src2_start)) src2_start++;
            strncpy(src2, src2_start, sizeof(src2) - 1);
            src2[sizeof(src2) - 1] = '\0';
            int src2_len = (int)strlen(src2);
            while (src2_len > 0 && isspace(src2[src2_len - 1])) {
                src2[--src2_len] = '\0';
            }
        } else if (op_pos_right >= 0) {
            /* Format: dest = src1 op src2 */
            strcpy(dest, left);
            strncpy(src1, right, op_pos_right);
            src1[op_pos_right] = '\0';
            int src1_len = (int)strlen(src1);
            while (src1_len > 0 && isspace(src1[src1_len - 1])) {
                src1[--src1_len] = '\0';
            }

            op = right[op_pos_right];
            const char *src2_start = right + op_pos_right + 1;
            while (*src2_start && isspace(*src2_start)) src2_start++;
            strncpy(src2, src2_start, sizeof(src2) - 1);
            src2[sizeof(src2) - 1] = '\0';
            int src2_len = (int)strlen(src2);
            while (src2_len > 0 && isspace(src2[src2_len - 1])) {
                src2[--src2_len] = '\0';
            }
        } else {
            fprintf(stderr, "Invalid format: %s (no operator found)\n", line);
            continue;
        }

        /* Map operator */
        switch (op) {
        case '+': strcpy(opr, "ADD"); break;
        case '-': strcpy(opr, "SUB"); break;
        case '*': strcpy(opr, "MUL"); break;
        case '/': strcpy(opr, "DIV"); break;
        default: strcpy(opr, "UNK"); break;
        }

        /* Generate target code */
        printf("\n\tMov %s, R%d", src1, i);
        printf("\n\t%s %s, R%d", opr, src2, i);
        printf("\n\tMov R%d, %s\n", i, dest);
    }

    return 0;
}