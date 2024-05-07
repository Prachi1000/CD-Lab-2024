#include <stdio.h>

void fcfsAlgorithm() {
    printf("First-Come, First-Served (FCFS) Scheduling Algorithm\n");

    int n, i, waiting_time = 0, turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n];

    printf("Enter the burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        turnaround_time += burst_time[i];
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time, turnaround_time);
        waiting_time += burst_time[i];
    }
}

void sjfAlgorithm() {
    printf("Shortest Job First (SJF) Scheduling Algorithm\n");

    int n, i, j, temp, waiting_time = 0, turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n];

    printf("Enter the burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    // Sorting processes based on burst time using bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (burst_time[j] > burst_time[j + 1]) {
                // Swap burst times
                temp = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp;
            }
        }
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        turnaround_time += burst_time[i];
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time, turnaround_time);
        waiting_time += burst_time[i];
    }
}

void prioritySchedulingAlgorithm() {
    printf("Priority Scheduling Algorithm\n");

    int n, i, j, temp, waiting_time = 0, turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], priority[n];

    printf("Enter the burst time and priority for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Priority for Process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Sorting processes based on priority using bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                // Swap burst times and priorities
                temp = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp;

                temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;
            }
        }
    }

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        turnaround_time += burst_time[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], priority[i], waiting_time, turnaround_time);
        waiting_time += burst_time[i];
    }
}

void srtfAlgorithm() {
    printf("Shortest Remaining Time First(SRTF) Scheduling Algorithm\n");

    int n, i, j, temp, time, min, remaining;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival_time[n], burst_time[n], remaining_time[n];

    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Arrival time for Process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    time = 0;

    printf("\nGantt Chart:\n");
    printf("0");

    for (time = 0; ; ) {
        min = n + 1;
        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] < remaining_time[min] && remaining_time[i] > 0) {
                min = i;
            }
        }

        if (min == n + 1)
            break;

        printf(" -> P%d -> %d", min + 1, time + 1);
        remaining_time[min]--;
        time++;

        if (remaining_time[min] == 0) {
            printf("\n");
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i],
               time - arrival_time[i] - burst_time[i] + remaining_time[i], time - arrival_time[i]);
    }
}

void roundRobinAlgorithm() {
    printf("Round Robin Scheduling Algorithm\n");

    int n, i, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n];

    printf("Enter the burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    int remaining_time[n];
    for (i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    int flag;
    int waiting_time = 0, turnaround_time = 0;

    do {
        flag = 0;
        for (i = 0; i < n; i++) {
                        if(remaining_time[i] > 0) {
                flag = 1;

                if (remaining_time[i] > time_quantum) {
                    printf("P%d -> %d -> ", i + 1, time_quantum);
                    waiting_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    printf("P%d -> %d -> ", i + 1, remaining_time[i]);
                    waiting_time += remaining_time[i];
                    remaining_time[i] = 0;
                    turnaround_time += waiting_time;
                }
            }
        }
    } while (flag);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time - burst_time[i], turnaround_time);
    }
}
int main() {
    int choice;

    do {
        // Display menu
        printf("\nScheduling Algorithm Menu\n");
        printf("1) FCFS\n");
        printf("2) SJF\n");
        printf("3) Priority Scheduling\n");
        printf("4) SRTF\n");
        printf("5) Round Robin\n");
        printf("6) Exit\n");

        // User input
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        // Switch case to display the chosen scheduling algorithm
        switch (choice) {
            case 1:
                fcfsAlgorithm();
                break;
            case 2:
                 sjfAlgorithm();
                break;
            case 3:
                prioritySchedulingAlgorithm();
                break;
            case 4:
                srtfAlgorithm();
                break;
            case 5:
                roundRobinAlgorithm();
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}