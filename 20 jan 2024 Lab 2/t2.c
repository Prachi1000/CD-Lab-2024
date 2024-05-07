#include <stdio.h>

#define VM_COUNT 3
#define TASK_COUNT 6

// Function to find maximum value in an array
int max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Function to find makespan using Surforage Heuristic
int surforage(int vms[], int tasks[][VM_COUNT], int sequence[]) {
    int completion_times[VM_COUNT] = {0}; // Initialize completion times for each VM

    for (int i = 0; i < TASK_COUNT; i++) {
        int vm = 0;
        int min_completion_time = completion_times[0] + tasks[i][0]; // Initialize with first VM
        for (int j = 1; j < VM_COUNT; j++) {
            int temp_completion_time = completion_times[j] + tasks[i][j];
            if (temp_completion_time < min_completion_time) {
                min_completion_time = temp_completion_time;
                vm = j; // Assign task to VM with minimum completion time
            }
        }
        completion_times[vm] = min_completion_time; // Update completion time of chosen VM
        sequence[i] = vm; // Store the VM index for the task in the sequence
    }

    // Return the makespan which is the maximum completion time among all VMs
    return max(completion_times, VM_COUNT);
}

// Function to find makespan using Min-Min Algorithm
int min_min(int vms[], int tasks[][VM_COUNT], int sequence[]) {
    int completion_times[VM_COUNT] = {0}; // Initialize completion times for each VM
    int tasks_completed[TASK_COUNT] = {0}; // Keep track of completed tasks

    for (int k = 0; k < TASK_COUNT; k++) {
        int min_processing_time = -1;
        int min_vm = -1;
        int min_task = -1;

        // Find the task with the minimum processing time that is not yet scheduled
        for (int i = 0; i < TASK_COUNT; i++) {
            if (!tasks_completed[i]) {
                for (int j = 0; j < VM_COUNT; j++) {
                    if (tasks[i][j] < min_processing_time || min_processing_time == -1) {
                        min_processing_time = tasks[i][j];
                        min_vm = j;
                        min_task = i;
                    }
                }
            }
        }

        // Schedule the task on the VM with the earliest completion time
        completion_times[min_vm] += min_processing_time;
        tasks_completed[min_task] = 1; // Mark task as completed
        sequence[k] = min_vm; // Store the VM index for the task in the sequence
    }

    // Return the makespan which is the maximum completion time among all VMs
    return max(completion_times, VM_COUNT);
}

// Function to find overall completion time
int overall_completion(int tasks[][VM_COUNT], int sequence[]) {
    int completion_times[TASK_COUNT] = {0};
    for (int i = 0; i < TASK_COUNT; i++) {
        int max_completion_time = 0;
        for (int j = 0; j < VM_COUNT; j++) {
            if (completion_times[i] + tasks[i][j] > max_completion_time) {
                max_completion_time = completion_times[i] + tasks[i][j];
            }
        }
        completion_times[i] = max_completion_time;
    }

    // Return the overall completion time, which is the maximum completion time among all tasks
    int overall_completion_time = max(completion_times, TASK_COUNT);

    // Store the sequence of tasks with their respective VM index
    for (int i = 0; i < TASK_COUNT; i++) {
        for (int j = 0; j < TASK_COUNT; j++) {
            if (completion_times[j] == overall_completion_time) {
                sequence[i] = j;
                completion_times[j] = -1; // Mark task as completed
                break;
            }
        }
    }

    return overall_completion_time;
}

int main() {
    int vms[VM_COUNT] = {110, 70, 50}; // Capacity of each VM
    int tasks[TASK_COUNT][VM_COUNT] = {
        {110, 50, 40},
        {70, 140, 110},
        {50, 80, 70},
        {50, 80, 110},
        {130, 90, 30},
        {140, 110, 60}
    };

    int sequence[TASK_COUNT]; // To store the sequence of tasks

    // SURF Heuristic
    int surf_makespan = surforage(vms, tasks, sequence);

    // Min-Min Algorithm
    int min_min_makespan = min_min(vms, tasks, sequence);

    // Determine which algorithm gives better results
    if (surf_makespan <= min_min_makespan) {
        printf("SURF Heuristic shows better result.\n");
        printf("Makespan using SURF Heuristic: %d\n", surf_makespan);
    } else {
        printf("Min-Min Algorithm shows better result.\n");
        printf("Makespan using Min-Min Algorithm: %d\n", min_min_makespan);
    }

    printf("Sequence of tasks:\n");
    for (int i = 0; i < TASK_COUNT; i++) {
        printf("T%d (VM%d)\n", i+1, sequence[i]+1);
    }

    // Overall completion time
    int overall_completion_time = overall_completion(tasks, sequence);
    printf("Overall completion time: %d\n", overall_completion_time);

    return 0;
}