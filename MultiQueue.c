#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    bool completed;
} Process;

void sort_by_arrival_time(Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int find_shortest_job(Process *processes, int n, int current_time) {
    int shortest_job_index = -1;
    int shortest_burst_time = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (processes[i].priority == 1 &&
            processes[i].arrival_time <= current_time &&
            !processes[i].completed &&
            processes[i].burst_time < shortest_burst_time) {
            shortest_burst_time = processes[i].burst_time;
            shortest_job_index = i;
        }
    }

    return shortest_job_index;
}

int find_first_arrived_job(Process *processes, int n, int current_time) {
    int first_arrived_index = -1;
    int earliest_arrival_time = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (processes[i].priority == 2 &&
            processes[i].arrival_time <= current_time &&
            !processes[i].completed &&
            processes[i].arrival_time < earliest_arrival_time) {
            earliest_arrival_time = processes[i].arrival_time;
            first_arrived_index = i;
        }
    }

    return first_arrived_index;
}

bool all_processes_completed(Process *processes, int n) {
    for (int i = 0; i < n; i++) {
        if (!processes[i].completed) {
            return false;
        }
    }
    return true;
}

int find_next_arrival_time(Process *processes, int n, int current_time) {
    int next_arrival = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!processes[i].completed && processes[i].arrival_time > current_time && processes[i].arrival_time < next_arrival) {
            next_arrival = processes[i].arrival_time;
        }
    }

    return next_arrival != INT_MAX ? next_arrival : current_time;
}

void print_process_table(Process *processes, int n) {
    printf("\nProcess\tPriority\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    printf("-------------------------------------------------------------------\n");

    float avg_waiting_time = 0, avg_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t%d\t%d\t\t%d\t%d\n",
               processes[i].id,
               processes[i].priority,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);

        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

void multilevel_queue_scheduling(Process *processes, int n) {
    sort_by_arrival_time(processes, n);

    int current_time = 0;

    while (!all_processes_completed(processes, n)) {
        int selected_process = -1;

        selected_process = find_shortest_job(processes, n, current_time);

        if (selected_process == -1) {
            selected_process = find_first_arrived_job(processes, n, current_time);
        }

        if (selected_process == -1) {
            int next_time = find_next_arrival_time(processes, n, current_time);
            current_time = next_time;
            continue;
        }

        current_time += processes[selected_process].burst_time;
        processes[selected_process].completion_time = current_time;
        processes[selected_process].turnaround_time =
            processes[selected_process].completion_time - processes[selected_process].arrival_time;
        processes[selected_process].waiting_time =
            processes[selected_process].turnaround_time - processes[selected_process].burst_time;
        processes[selected_process].completed = true;
    }

    print_process_table(processes, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    printf("Enter id, priority, arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &processes[i].id, &processes[i].priority, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].completed = false;
    }

    printf("\nMultilevel Queue Scheduling (Priority 1: SJF, Priority 2: FCFS)\n");
    multilevel_queue_scheduling(processes, n);

    free(processes);
    return 0;
}
