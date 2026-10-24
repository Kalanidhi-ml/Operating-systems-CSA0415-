#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int priority;
    int rt;
    int ct;
    int tat;
    int wt;
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
        printf("Enter Priority (lower value = higher priority): ");
        scanf("%d", &p[i].priority);
        
        p[i].rt = p[i].bt;
    }

    int completed = 0, time = 0, shortest = -1;
    int min_prio;
    float total_tat = 0, total_wt = 0;

    while (completed < n) {
        shortest = -1;
        min_prio = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].priority < min_prio) {
                min_prio = p[i].priority;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        p[shortest].rt--;
        time++;

        if (p[shortest].rt == 0) {
            completed++;
            p[shortest].ct = time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;

            total_tat += p[shortest].tat;
            total_wt += p[shortest].wt;
        }
    }

    printf("\n--- PREEMPTIVE PRIORITY SCHEDULING RESULTS ---\n");
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].priority, 
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}