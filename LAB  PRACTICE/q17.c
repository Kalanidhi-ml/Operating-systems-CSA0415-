#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m; // n = number of processes, m = number of resources
int alloc[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int avail[MAX_RESOURCES];

// Function to calculate the Need Matrix
void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Function to check if the system is in a Safe State
bool isSafeState(int safeSeq[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    // Initialize Work = Available
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                // If resources can be allocated to process p
                if (canAllocate) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        // If no process could be allocated resources in a full cycle
        if (!found) {
            return false; // System is in an Unsafe State
        }
    }
    return true; // System is in a Safe State
}

// Function to handle dynamic Resource Request
void requestResources(int p_id, int req[]) {
    // Step 1: Check if Request <= Need
    for (int j = 0; j < m; j++) {
        if (req[j] > need[p_id][j]) {
            printf("\nERROR: Process P%d exceeded its maximum declared claim!\n", p_id);
            return;
        }
    }

    // Step 2: Check if Request <= Available
    for (int j = 0; j < m; j++) {
        if (req[j] > avail[j]) {
            printf("\nProcess P%d must WAIT. Requested resources not available.\n", p_id);
            return;
        }
    }

    // Step 3: Pre-allocate resources speculatively
    for (int j = 0; j < m; j++) {
        avail[j] -= req[j];
        alloc[p_id][j] += req[j];
        need[p_id][j] -= req[j];
    }

    // Step 4: Test Safety
    int safeSeq[MAX_PROCESSES];
    if (isSafeState(safeSeq)) {
        printf("\nSUCCESS: Request granted to Process P%d!\n", p_id);
        printf("New Safe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("\nREJECTED: Request causes system to enter an UNSAFE STATE! Rolling back...\n");
        // Rollback state changes
        for (int j = 0; j < m; j++) {
            avail[j] += req[j];
            alloc[p_id][j] -= req[j];
            need[p_id][j] += req[j];
        }
    }
}

int main() {
    // Initializing sample data (3 processes, 3 resource types A, B, C)
    n = 3; 
    m = 3; 

    // Allocation Matrix
    int sampleAlloc[3][3] = {
        {1, 0, 1}, // P0
        {0, 1, 0}, // P1
        {1, 1, 1}  // P2
    };

    // Maximum Matrix
    int sampleMax[3][3] = {
        {2, 1, 2}, // P0
        {1, 2, 1}, // P1
        {3, 2, 2}  // P2
    };

    // Available Resources
    int sampleAvail[3] = {2, 1, 1};

    // Copying sample data into global matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            alloc[i][j] = sampleAlloc[i][j];
            max[i][j] = sampleMax[i][j];
        }
    }
    for (int j = 0; j < m; j++) {
        avail[j] = sampleAvail[j];
    }

    calculateNeed();

    printf("=== Initial System Safety Check ===\n");
    int safeSeq[MAX_PROCESSES];
    if (isSafeState(safeSeq)) {
        printf("System is in a SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("System is in an UNSAFE state.\n");
    }

    // Simulating Resource Request from Process P1
    printf("\n=== Simulating Resource Request ===");
    int p_id = 1; // Process P1
    int req[3] = {1, 0, 1}; // P1 requests (1, 0, 1)

    printf("\nProcess P%d requests resources: (", p_id);
    for (int j = 0; j < m; j++) printf("%d ", req[j]);
    printf(")\n");

    requestResources(p_id, req);

    return 0;
}