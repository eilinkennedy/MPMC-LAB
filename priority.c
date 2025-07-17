#include <stdio.h>

void main() {
    int i, n;
    float avg_wt = 0.0, avg_tat = 0.0;
    int total_wt = 0, total_tat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int waiting_time[n], tatime[n];
    int burst_time[n], priority[n];
    
    // Input burst time and priority for each process
    for (i = 0; i < n; i++) {
        printf("Enter the burst time for P%d: ", (i + 1));
        scanf("%d", &burst_time[i]);
        printf("Enter the priority for P%d: ", (i + 1));
        scanf("%d", &priority[i]);
    }
    
    // Sorting processes based on priority (ascending order)
    for (i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (priority[i] > priority[j]) {
                // Swap burst time
                int temp_burst = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp_burst;
                
                // Swap priority
                int temp_priority = priority[i];
                priority[i] = priority[j];
                priority[j] = temp_priority;
                
                // Swap waiting time (to maintain consistency)
                int temp_waiting = waiting_time[i];
                waiting_time[i] = waiting_time[j];
                waiting_time[j] = temp_waiting;
                
                // Swap turnaround time (to maintain consistency)
                int temp_tat = tatime[i];
                tatime[i] = tatime[j];
                tatime[j] = temp_tat;
            }
        }
    }

    // Calculate waiting time
    waiting_time[0] = 0;
    for (i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
        total_wt += waiting_time[i];
    }
    avg_wt = total_wt / n;

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        tatime[i] = burst_time[i] + waiting_time[i];
        total_tat += tatime[i];
    }
    avg_tat = total_tat / n;

    // Display in table format
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", (i + 1), burst_time[i], priority[i], waiting_time[i], tatime[i]);
    }

    printf("The average waiting time is %.2f\n", avg_wt);
    printf("The average turnaround time is %.2f\n", avg_tat);

    // Print Gantt Chart
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

    int current_time = 0;
    printf("0");
    for (i = 0; i < n; i++) {
        current_time += burst_time[i];
        printf("     %d", current_time);
    }
    printf("\n");
}
