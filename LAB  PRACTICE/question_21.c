#include <stdio.h>

#define MAX 100

int main() {
    int m, n;
    int blockSize[MAX], processSize[MAX], allocation[MAX];

    if (scanf("%d", &m) != 1 || m <= 0 || m > MAX) return 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) return 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    printf("\nRemaining Block Sizes:\n");
    for (int j = 0; j < m; j++) {
        printf("Block %d: %d\n", j + 1, blockSize[j]);
    }

    return 0;
}