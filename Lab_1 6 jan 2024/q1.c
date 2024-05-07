#include <stdio.h>
#include <limits.h>

void findWaitingTimeFCFS(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findTurnAroundTimeFCFS(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

float findAverageTimeFCFS(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTimeFCFS(processes, n, bt, wt);
    findTurnAroundTimeFCFS(processes, n, bt, wt, tat);

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("FCFS:\n");
    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n\n", (float)total_tat / (float)n);
    return ((float)total_tat / (float)n);
}

void findWaitingTimeSJF(int processes[], int n, int bt[], int wt[]) {
    int rt[n];
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int complete = 0, t = 0, minm = INT_MAX, shortest = 0, finish_time;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((rt[j] <= t) && (rt[j] < minm) && (rt[j] > 0)) {
                minm = rt[j];
                shortest = j;
            }
        }

        rt[shortest] = 0;
        minm = INT_MAX;

        if (rt[shortest] == 0) {
            complete++;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        t++;
    }
}

void findTurnAroundTimeSJF(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

float findAverageTimeSJF(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTimeSJF(processes, n, bt, wt);
    findTurnAroundTimeSJF(processes, n, bt, wt, tat);

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("SJF:\n");
    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n\n", (float)total_tat / (float)n);
    return ((float)total_tat / (float)n); 
}

void findWaitingTimeRR(int processes[], int n, int bt[], int wt[], int quantum) {
    int remaining_bt[n];
    for (int i = 0; i < n; i++)
        remaining_bt[i] = bt[i];

    int t = 0;

    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                done = 0;

                if (remaining_bt[i] > quantum) {
                    t += quantum;
                    remaining_bt[i] -= quantum;
                } else {
                    t += remaining_bt[i];
                    wt[i] = t - bt[i];
                    remaining_bt[i] = 0;
                }
            }
        }

        if (done == 1)
            break;
    }
}

void findTurnAroundTimeRR(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

float findAverageTimeRR(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTimeRR(processes, n, bt, wt, quantum);
    findTurnAroundTimeRR(processes, n, bt, wt, tat);

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Round Robin:\n");
    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n\n", (float)total_tat / (float)n);
    return ((float)total_tat / (float)n);
}
void print_min(float a,float b ,float c){
    float shortest=0.0;
    if(a<b){
         printf("\nshortest turn around time is by RR %f",a);
        shortest=a;
    }else{
         printf("\nshortest turn around time is byFCFS %f",b);
        shortest =b;
        
    }
    if(c<shortest){
        printf("shortest turn around time  is SJf: %f",c);
    }
    
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {1, 4, 6};
    int time_quantum ;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n];

    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

     printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

   float a= findAverageTimeFCFS(processes, n, burst_time);
  float b=  findAverageTimeSJF(processes, n, burst_time);
  float c= findAverageTimeRR(processes, n, burst_time, time_quantum);
  
  
print_min(a,b,c);

    return 0;
}