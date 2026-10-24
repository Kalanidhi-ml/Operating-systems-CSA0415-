#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:\n", p[i].pid);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].completed = 0;
    }

    int completed = 0, time = 0;
    float total_tat = 0, total_wt = 0;

    while (completed < n) {
        int shortest = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    shortest = i;
                }
                if (p[i].bt == min_bt) {
                    if (p[i].at < p[shortest].at) {
                        min_bt = p[i].bt;
                        shortest = i;
                    }
                }
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        time += p[shortest].bt;
        p[shortest].ct = time;
        p[shortest].tat = p[shortest].ct - p[shortest].at;
        p[shortest].wt = p[shortest].tat - p[shortest].bt;
        p[shortest].completed = 1;
        completed++;

        total_tat += p[shortest].tat;
        total_wt += p[shortest].wt;
    }

    printf("\n--- NON-PREEMPTIVE SJF SCHEDULING RESULTS ---\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, 
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}