#include <stdio.h>
#include <string.h>

#define MAX_P 10
#define MAX_R 10

int alloc[MAX_P][MAX_R], max[MAX_P][MAX_R], avail[MAX_R], need[MAX_P][MAX_R];
int done[MAX_P], seq[MAX_P], np, nr;

void calc_need() {
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

int is_safe() {
    int count = 0;
    while (count < np) {
        int found = 0;
        for (int i = 0; i < np; i++) {
            if (!done[i]) {
                int j;
                for (j = 0; j < nr; j++)
                    if (need[i][j] > avail[j]) break;
                if (j == nr) {
                    for (int k = 0; k < nr; k++)
                        avail[k] += alloc[i][k];
                    seq[count++] = i;
                    done[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }
    return count == np;
}

int main() {
    printf("Processes: "); scanf("%d", &np);
    printf("Resources: "); scanf("%d", &nr);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int j = 0; j < nr; j++)
        scanf("%d", &avail[j]);

    calc_need();
    memset(done, 0, sizeof(done));

    if (is_safe()) {
        printf("System is in safe state\nSafe sequence: ");
        for (int i = 0; i < np; i++)
            printf("P%d%s", seq[i], (i == np - 1) ? "\n" : " -> ");
    } else {
        printf("System is in unsafe state\n");
    }
    return 0;
}
