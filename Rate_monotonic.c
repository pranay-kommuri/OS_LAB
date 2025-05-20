#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    int period;
    int execution;
    int deadline;
    int next_arrival;
    int remaining;
} Task;

int compare_periods(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;

    return taskA->period - taskB->period;
}

bool is_schedulable(Task *tasks, int n) {
    double utilization = 0.0;
    for (int i = 0; i < n; i++) {
        utilization += (double)tasks[i].execution / tasks[i].period;
    }

    double bound;
    if (n == 1) bound = 1.0;
    else if (n == 2) bound = 0.8284;
    else bound = (double)n * (pow(2.0, 1.0/n) - 1.0);

    printf("Utilization: %.4f, Schedulability Bound: %.4f\n", utilization, bound);
    return utilization <= bound;
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

    qsort(tasks, n, sizeof(Task), compare_periods);

    printf("\nTasks sorted by priority (Rate Monotonic):\n");
    printf("Task ID\tPeriod\tExecution\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\n", tasks[i].id, tasks[i].period,
               tasks[i].execution, i + 1);
    }

    if (!is_schedulable(tasks, n)) {
        printf("\nWARNING: The task set may not be schedulable using Rate Monotonic scheduling!\n");
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
    printf("\nRate Monotonic Scheduling Simulation:\n");
    printf("Time\tExecuting Task\n");

    for (current_time = 0; current_time < hyperperiod; current_time++) {
        for (int i = 0; i < n; i++) {
            if (current_time % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].next_arrival = current_time + tasks[i].period;
            }
        }

        int selected_task = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                selected_task = i;
                break;
            }
        }

        if (selected_task != -1) {
            tasks[selected_task].remaining--;
            printf("%d\tTask %d\n", current_time, tasks[selected_task].id);
        } else {
            printf("%d\tIdle\n", current_time);
            idle_time++;
        }
    }

    printf("\nSimulation complete. Idle time: %d units (%.2f%%)\n",
           idle_time, ((float)idle_time / hyperperiod) * 100);

    free(tasks);
    return 0;
}
