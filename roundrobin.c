#include <stdio.h>

void main() {
    int i, n, time_quantum;
    float avg_wt = 0.0, avg_tat = 0.0;
    int total_wt = 0, total_tat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int waiting_time[n], tatime[n];
    int burst_time[n], remaining_burst_time[n];
    int arrival_time[n], turnaround_time[n];

    // Input burst time and arrival time for each process
    for (i = 0; i < n; i++) {
        printf("Enter the burst time for P%d: ", (i + 1));
        scanf("%d", &burst_time[i]);
        remaining_burst_time[i] = burst_time[i];
        arrival_time[i] = 0; // assuming all processes arrive at time 0 for simplicity
    }

    // Input time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    int current_time = 0;
    int remaining_processes = n;
    
    // Round Robin Scheduling
    while (remaining_processes > 0) {
        for (i = 0; i < n; i++) {
            if (remaining_burst_time[i] > 0) {
                // Execute process for time quantum or the remaining burst time, whichever is smaller
                int executed_time = (remaining_burst_time[i] < time_quantum) ? remaining_burst_time[i] : time_quantum;
                remaining_burst_time[i] -= executed_time;
                current_time += executed_time;

                // If the process has finished, calculate its turnaround and waiting times
                if (remaining_burst_time[i] == 0) {
                    turnaround_time[i] = current_time - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];
                    total_wt += waiting_time[i];
                    total_tat += turnaround_time[i];
                    remaining_processes--;
                }
            }
        }
    }

    // Calculate averages
    avg_wt = (float) total_wt / n;
    avg_tat = (float) total_tat / n;

    // Display in table format
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", (i + 1), burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nThe average waiting time is %.2f\n", avg_wt);
    printf("The average turnaround time is %.2f\n", avg_tat);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("| P%d  ", (i + 1));
    }
    printf("|\n");
    for (i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n");

    current_time = 0;
    printf("0");
    for (i = 0; i < n; i++) {
        current_time += burst_time[i];
        printf("     %d", current_time);
    }
    printf("\n");
}
