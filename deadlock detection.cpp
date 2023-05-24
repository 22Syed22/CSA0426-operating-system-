#include <stdio.h>

#define N 3 // number of processes and resources

int main() {
    // initialize the max and allocation matrices
    int max[N][N] = {{3, 6, 8}, {4, 3, 3}, {3, 4, 4}};
    int allocation[N][N] = {{3, 3, 3}, {2, 0, 3}, {1, 2, 4}};

    // calculate the need matrix
    int need[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // initialize the work and finish arrays
    int work[N];
    int finish[N] = {0};

    // initialize the work array with the available resources
    int available[N] = {2, 3, 2};
    for (int i = 0; i < N; i++) {
        work[i] = available[i];
    }

    // iterate over the processes until all are finished or deadlock is detected
    int count = 0;
    while (count < N) {
        int found = 0;
        for (int i = 0; i < N; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < N; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == N) {
                    // process i can finish
                    finish[i] = 1;
                    found = 1;
                    count++;
                    for (int k = 0; k < N; k++) {
                        work[k] += allocation[i][k];
                    }
                }
            }
        }
        if (!found) {
            // deadlock detected
            printf("Deadlock detected!\n");
            return 0;
        }
    }

    // no deadlock detected
    printf("No deadlock detected.\n");
    return 0;
}
