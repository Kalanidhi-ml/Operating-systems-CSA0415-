#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n, tq;
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
        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};

    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        if (p[idx].rt > tq) {
            time += tq;
            p[idx].rt -= tq;
        } else {
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
        }

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].rt > 0) {
            queue[rear++] = idx;
        }
    }

    printf("\n--- ROUND ROBIN SCHEDULING RESULTS ---\n");
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