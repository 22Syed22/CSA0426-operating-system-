#include <stdio.h>

#define MAX_PROCESSES 4   // maximum number of processes

struct Process {
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    struct Process processes[MAX_PROCESSES];
    float avg_waiting_time = 0.0;
    float avg_turnaround_time = 0.0;

    // initialize processes
    processes[0].burst_time = 6;
    processes[1].burst_time = 8;
    processes[2].burst_time = 7;
    processes[3].burst_time = 3;

    // sort processes by burst time (ascending order)
    int i, j;
    for (i = 0; i < MAX_PROCESSES - 1; i++) {
        for (j = i + 1; j < MAX_PROCESSES; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                // swap processes[i] and processes[j]
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // compute waiting time and turnaround time for each process
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    for (i = 0; i < MAX_PROCESSES; i++) {
        // calculate waiting time for current process
        processes[i].waiting_time = current_time;
        total_waiting_time += processes[i].waiting_time;

        // calculate turnaround time for current process
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        total_turnaround_time += processes[i].turnaround_time;

        // update current time
        current_time += processes[i].burst_time;
    }

    // calculate average waiting time and average turnaround time
    avg_waiting_time = (float) total_waiting_time / MAX_PROCESSES;
    avg_turnaround_time = (float) total_turnaround_time / MAX_PROCESSES;

    // print results
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < MAX_PROCESSES; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i+1, processes[i].burst_time,
            processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
