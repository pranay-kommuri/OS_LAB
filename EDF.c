#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int id;
    int period;
    int execution;
    int deadline;
    int next_arrival;
    int remaining;
} Task;

int get_earliest_deadline_task(Task *tasks, int n, int current_time) {
    int earliest_task = -1;
    int min_deadline = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (tasks[i].remaining > 0 && tasks[i].deadline < min_deadline) {
            min_deadline = tasks[i].deadline;
            earliest_task = i;
        }
    }

    return earliest_task;
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task *tasks = (Task *)malloc(n * sizeof(Task));

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter period for Task %d: ", i + 1);
        scanf("%d", &tasks[i].period);
        printf("Enter execution time for Task %d: ", i + 1);
        scanf("%d", &tasks[i].execution);
        tasks[i].deadline = tasks[i].period;
        tasks[i].next_arrival = 0;
        tasks[i].remaining = 0;
    }

    double utilization = 0.0;
    for (int i = 0; i < n; i++) {
        utilization += (double)tasks[i].execution / tasks[i].period;
    }

    printf("\nUtilization: %.4f\n", utilization);
    if (utilization > 1.0) {
        printf("WARNING: The task set is not schedulable using EDF (utilization > 1)!\n");
    } else {
        printf("The task set is theoretically schedulable using EDF (utilization <= 1).\n");
    }

    int current_time = 0;
    int hyperperiod = 1;
    int idle_time = 0;

    for (int i = 0; i < n; i++) {
        int a = hyperperiod;
        int b = tasks[i].period;
        int temp;

        while (b != 0) {
            temp = b;
            b = a % b;
            a = temp;
        }

        hyperperiod = (hyperperiod * tasks[i].period) / a;
    }

    printf("\nHyperperiod: %d\n", hyperperiod);
    printf("\nEarliest Deadline First Scheduling Simulation:\n");
    printf("Time\tExecuting Task\tTasks with deadlines\n");

    for (current_time = 0; current_time < hyperperiod; current_time++) {
        for (int i = 0; i < n; i++) {
            if (current_time % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].deadline = current_time + tasks[i].period;
                tasks[i].next_arrival = current_time + tasks[i].period;
            }
        }

        int selected_task = get_earliest_deadline_task(tasks, n, current_time);

        printf("%d\t", current_time);
        if (selected_task != -1) {
            tasks[selected_task].remaining--;
            printf("Task %d\t\t", tasks[selected_task].id);
        } else {
            printf("Idle\t\t");
            idle_time++;
        }

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                printf("T%d(d:%d) ", tasks[i].id, tasks[i].deadline);
            }
        }
        printf("\n");

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0 && current_time + 1 == tasks[i].deadline) {
                if (selected_task != i) {
                    printf("DEADLINE MISS: Task %d at time %d\n", tasks[i].id, current_time + 1);
                }
            }
        }
    }

    printf("\nSimulation complete. Idle time: %d units (%.2f%%)\n",
           idle_time, ((float)idle_time / hyperperiod) * 100);

    free(tasks);
    return 0;
}
