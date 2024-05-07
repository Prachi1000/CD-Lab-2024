#include <stdio.h>
#include <limits.h>

#define MAX_TASKS 100
#define MAX_MACHINES 10

struct Task {
    int taskID;
    int execTime;
    int machineID; // To keep track of assigned machine
};

struct Machine {
    int machineID;
    int totalTime;
};

int findMinExecutionTimeTask(struct Task tasks[], int n) {
    int minExecTime = INT_MAX;
    int minExecTimeTask = -1;

    for (int i = 0; i < n; i++) {
        if (tasks[i].execTime != INT_MAX && tasks[i].execTime < minExecTime) {
            minExecTime = tasks[i].execTime;
            minExecTimeTask = i;
        }
    }

    return minExecTimeTask;
}

int findMinTotalTimeMachine(struct Machine machines[], int m) {
    int minTotalTime = INT_MAX;
    int minTotalTimeMachine = -1;

    for (int i = 0; i < m; i++) {
        if (machines[i].totalTime < minTotalTime) {
            minTotalTime = machines[i].totalTime;
            minTotalTimeMachine = i;
        }
    }

    return minTotalTimeMachine;
}

void minMinScheduling(struct Task tasks[], int n, struct Machine machines[], int m) {
    printf("\n           ");
    for (int i = 0; i < n; i++) {
        printf("T%d ", i);
    }
    printf("\n");

    for (int i = 0; i < m; i++) {
        printf("M%d     ", i);
        for (int j = 0; j < n; j++) {
            printf("%2d ", tasks[i * n + j].execTime);
        }
        printf("\n");
    }

    printf("\nPerforming Min-min scheduling...\n");

    for (int i = 0; i < n; i++) {
        int taskID = findMinExecutionTimeTask(tasks, n);
        int machineID = findMinTotalTimeMachine(machines, m);

        tasks[taskID].machineID = machineID;
        machines[machineID].totalTime += tasks[taskID].execTime;
        tasks[taskID].execTime = INT_MAX;

        printf("Task[%d] -> Machine[%d]\n", tasks[taskID].taskID, machines[machineID].machineID);
    }
}

int main() {
    int n, m;
    struct Task tasks[MAX_TASKS];
    struct Machine machines[MAX_MACHINES];

    printf("Enter the number of machines and number of tasks: ");
    scanf("%d %d", &m, &n);

    printf("Enter the execution time for each machine-task pair:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter time for Machine %d, Task %d: ", i, j);
            scanf("%d", &tasks[i * n + j].execTime);
            tasks[i * n + j].taskID = j;
            tasks[i * n + j].machineID = -1; // Initialize with an invalid value
        }
    }

    for (int i = 0; i < m; i++) {
        machines[i].machineID = i;
        machines[i].totalTime = 0;
    }

    minMinScheduling(tasks, n, machines, m);

    return 0;
}