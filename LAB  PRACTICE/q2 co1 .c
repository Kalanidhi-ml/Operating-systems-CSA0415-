#include <stdio.h>

int main() {
    int n;
    int i;
    int bt[20];
    int wt[20];
    int tat[20];
    int total_wt;
    int total_tat;
    float avg_wt;
    float avg_tat;

    total_wt = 0;
    total_tat = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
    }

    avg_wt = (float)total_wt / (float)n;
    avg_tat = (float)total_tat / (float)n;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}