#include <stdio.h>

int main() {
    int n, i, j, t;
    int pid[20], bt[20], pr[20], wt[20], tat[20];
    int wt_sum, tat_sum;
    float awt, atat;

    wt_sum = 0;
    tat_sum = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        scanf("%d %d", &bt[i], &pr[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (pr[i] > pr[j]) {
                t = pr[i];
                pr[i] = pr[j];
                pr[j] = t;

                t = bt[i];
                bt[i] = bt[j];
                bt[j] = t;

                t = pid[i];
                pid[i] = pid[j];
                pid[j] = t;
            }
        }
    }

    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        wt_sum = wt_sum + wt[i];
        tat_sum = tat_sum + tat[i];
    }

    awt = (float)wt_sum / n;
    atat = (float)tat_sum / n;

    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", awt);
    printf("Average Turnaround Time: %.2f\n", atat);

    return 0;
}