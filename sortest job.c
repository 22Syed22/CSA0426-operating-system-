#include <stdio.h>
#include <limits.h>

// Structure to represent a process
typedef struct {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time of the process
    int burstTime;     // Burst time of the process
    int remainingTime; // Remaining burst time of the process
    int waitingTime;   // Waiting time of the process
} Process;

void sjfPreemptive(Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;
    int shortestIndex;

    while (completedProcesses < n) {
        shortestIndex = -1;
        int shortestBurst = INT_MAX;

        // Find the process with the shortest remaining burst time among the arrived processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestBurst && processes[i].remainingTime > 0) {
                shortestIndex = i;
                shortestBurst = processes[i].remainingTime;
            }
        }

        // If no process is found, increment the current time
        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        // Execute the process with the shortest remaining burst time for 1 unit
        processes[shortestIndex].remainingTime--;
        currentTime++;

        // Update waiting time for other processes
        for (int i = 0; i < n; i++) {
            if (i != shortestIndex && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                processes[i].waitingTime++;
            }
        }

        // Check if the process is completed
        if (processes[shortestIndex].remainingTime == 0) {
            printf("Process %d completed at time %d\n", processes[shortestIndex].pid, currentTime);
            completedProcesses++;
        }
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Create an array of processes
    Process processes[n];

    // Read process details from the user
    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
    }

    sjfPreemptive(processes, n);

    // Calculate average waiting time
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
    }
    double averageWaitingTime = (double)totalWaitingTime / n;

    printf("Average waiting time: %.2lf\n", averageWaitingTime);

    return 0;
}
