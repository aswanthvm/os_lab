#include <stdio.h>
#include <limits.h>

typedef struct {
    int id, at, bt, pri, ct, tat, wt, done;
} P;

void sortByArrival(P p[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].at > p[j].at) {
                P tmp = p[i]; p[i] = p[j]; p[j] = tmp;
            }
}

void priorityScheduling(P p[], int n) {
    int time = 0, done = 0;
    float twt = 0, ttat = 0;
    sortByArrival(p, n);

    while (done < n) {
        int idx = -1, high = INT_MAX;
        for (int i = 0; i < n; i++)
            if (!p[i].done && p[i].at <= time && p[i].pri < high) {
                high = p[i].pri;
                idx = i;
            }

        if (idx == -1) time++;
        else {
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            time = p[idx].ct;
            p[idx].done = 1;
            done++;
            twt += p[idx].wt;
            ttat += p[idx].tat;
        }
    }

    printf("\nID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAvg WT = %.2f\nAvg TAT = %.2f\n", twt/n, ttat/n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    P p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT, BT, Priority for P%d: ", p[i].id);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pri);
        p[i].done = 0;
    }

    printf("\nNon-Preemptive Priority Scheduling:\n");
    priorityScheduling(p, n);
    return 0;
}
