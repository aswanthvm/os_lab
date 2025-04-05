#include <stdio.h>

typedef struct {
    int id, at, bt, ct, tat, wt;
} P;

void sort_bt(P p[], int n, int time) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[j].at <= time && p[i].bt > p[j].bt) {
                P tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
}

void SJF(P p[], int n) {
    int time = 0;
    float ttat = 0, twt = 0;

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].at > p[j].at) {
                P tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }

    for (int i = 0; i < n; i++) {
        sort_bt(p, n, time);
        if (time < p[i].at)
            time = p[i].at;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time = p[i].ct;
        ttat += p[i].tat;
        twt += p[i].wt;
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAvg WT: %.2f\nAvg TAT: %.2f\n", twt / n, ttat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    P p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i + 1);
        p[i].id = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    SJF(p, n);
    return 0;
}
