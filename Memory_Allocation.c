#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define MAX_BLOCKS 10

// Function to implement First-Fit allocation
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initially, no process is allocated
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Find suitable blocks for each process
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= blockSize[j];
                break;
            }
        }
    }

    // Print allocation result
    printf("\nFirst-Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

// Function to implement Best-Fit allocation
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initially, no process is allocated
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Find suitable blocks for each process
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] =0;
        }
    }

    // Print allocation result
    printf("\nBest-Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

// Function to implement Worst-Fit allocation
void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initially, no process is allocated
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Find suitable blocks for each process
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[worstIdx] < blockSize[j]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] = 0;
        }
    }

    // Print allocation result
    printf("\nWorst-Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int blockF[MAX_BLOCKS],blockB[MAX_BLOCKS],blockW[MAX_BLOCKS];
    int m, n;

    // Input the number of blocks and processes
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the size of each block
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
        blockF[i]=blockSize[i];
        blockB[i]=blockSize[i];
        blockW[i]=blockSize[i];
    }

    // Input the size of each process
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    // Call each of the allocation functions
    firstFit(blockF, m, processSize, n);
    bestFit(blockB, m, processSize, n);
    worstFit(blockW , m, processSize, n);

    return 0;
}
