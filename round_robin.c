#include <stdio.h>

typedef struct {
    int id, at, bt;
} P;

void RR(P p[], int n, int tq) {
    int rt[n], wt[n], tat[n], ct[n], done = 0, time = 0;
    for (int i = 0; i < n; i++) rt[i] = p[i].bt;

    while (done < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && p[i].at <= time) {
                executed = 1;
                if (rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    tat[i] = ct[i] - p[i].at;
                    wt[i] = tat[i] - p[i].bt;
                    done++;
                } else {
                    rt[i] -= tq;
                    time += tq;
                }
            }
        }
        if (!executed) time++;  
    }

    float awt = 0, atat = 0;
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, ct[i], tat[i], wt[i]);
        awt += wt[i];
        atat += tat[i];
    }
    printf("\nAvg WT: %.2f\nAvg TAT: %.2f\n", awt/n, atat/n);
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    P p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nRound Robin Scheduling with Arrival Time:\n");
    RR(p, n, tq);
    return 0;
}
