#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct op {
    char l;
    char r[128];
};

int main(void) {
    struct op op[20], pr[20];
    int i, j, n, z = 0, k, pos;
    char temp, t;
    char *p, *l;

    printf("Enter the Number of Values: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) {
        fprintf(stderr, "Invalid number of values (1..20 expected)\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        /* read left operand (single char) */
        printf("left: ");
        if (scanf(" %c", &op[i].l) != 1) {
            fprintf(stderr, "Failed to read left operand\n");
            return 1;
        }
        /* read right side (string) */
        printf("\tright: ");
        if (scanf(" %127s", op[i].r) != 1) {
            fprintf(stderr, "Failed to read right expression\n");
            return 1;
        }
    }

    printf("\nIntermediate Code\n");
    for (i = 0; i < n; i++) {
        printf("%c = %s\n", op[i].l, op[i].r);
    }

    /* Build list of reachable / used expressions */
    for (i = 0; i < n - 1; i++) {
        temp = op[i].l;
        for (j = 0; j < n; j++) {
            p = strchr(op[j].r, temp);
            if (p) {
                pr[z].l = op[i].l;
                strncpy(pr[z].r, op[i].r, sizeof(pr[z].r) - 1);
                pr[z].r[sizeof(pr[z].r) - 1] = '\0';
                z++;
                break; /* add op[i] only once */
            }
        }
    }
    /* Always include last op (as original did) */
    pr[z].l = op[n - 1].l;
    strncpy(pr[z].r, op[n - 1].r, sizeof(pr[z].r) - 1);
    pr[z].r[sizeof(pr[z].r) - 1] = '\0';
    z++;

    printf("\nAfter Dead Code Elimination\n");
    for (k = 0; k < z; k++) {
        printf("%c = %s\n", pr[k].l, pr[k].r);
    }

    /* Replace occurrences to propagate newer temps (common-subexpression style) */
    for (int m = 0; m < z; m++) {
        char *tem = pr[m].r;
        for (j = m + 1; j < z; j++) {
            if (strstr(tem, pr[j].r)) {
                /* if pr[j].r appears in pr[m].r, replace pr[j].l with pr[m].l */
                t = pr[j].l;
                pr[j].l = pr[m].l;
                /* replace occurrences of t in all right sides with pr[m].l */
                for (i = 0; i < z; i++) {
                    l = strchr(pr[i].r, t);
                    while (l) {
                        pos = (int)(l - pr[i].r);
                        pr[i].r[pos] = pr[m].l;
                        /* continue searching after the replaced position */
                        l = strchr(pr[i].r + pos + 1, t);
                    }
                }
            }
        }
    }

    printf("\nEliminate Common Expression\n");
    /* Remove duplicates where left and right both match */
    for (i = 0; i < z; i++) {
        for (j = i + 1; j < z; j++) {
            if (pr[i].l != '\0' && pr[j].l != '\0' && pr[i].l == pr[j].l && strcmp(pr[i].r, pr[j].r) == 0) {
                pr[i].l = '\0';
                pr[i].r[0] = '\0';
            }
        }
    }

    printf("\nOptimized Code\n");
    for (i = 0; i < z; i++) {
        if (pr[i].l != '\0') {
            printf("%c = %s\n", pr[i].l, pr[i].r);
        }
    }

    return 0;
}