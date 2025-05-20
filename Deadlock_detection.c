
#include <stdio.h>
#include <stdbool.h>

int main() {
    int num_processes, num_resources;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    int allocation[num_processes][num_resources];
    int request[num_processes][num_resources];
    int available[num_resources];
    bool finish[num_processes];
    int work[num_resources];

    // Input Allocation Matrix
    printf("\nEnter the Allocation Matrix (%d x %d):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Request Matrix
    printf("\nEnter the Request Matrix (%d x %d):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter the Available Resources (%d):\n", num_resources);
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i]; // initialize work array
    }

    for (int i = 0; i < num_processes; i++) {
        finish[i] = false;
    }

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < num_resources; j++) {
                    if (request[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    changed = true;
                }
            }
        }
    } while (changed);

    // Check for unfinished processes
    bool deadlock = false;
    for (int i = 0; i < num_processes; i++) {
        if (!finish[i]) {
            deadlock = true;
            break;
        }
    }

    if (deadlock) {
        printf("\nDeadlock detected!\n");
    } else {
        printf("\nNo deadlock detected.\n");
    }

    return 0;
}
