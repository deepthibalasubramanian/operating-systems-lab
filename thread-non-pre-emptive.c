/*Write a C program to create 3 threads and execute(FCFS, non pre-emptive SJF, non pre-emptive PBS) in different threads and returns the process id which has the longest waiting time. Display the process id with longest waiting time in main().
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include<unistd.h>

#define NUM_THREADS 3

struct Process{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
};

void *fcfs(void *processes) {
    struct Process *p = (struct Process *) processes;
    int n = sizeof(p) / sizeof(p[0]);
    int wait_time = 0;
    for (int i = 0; i < n; i++) {
        p[i].waiting_time = wait_time;
        wait_time += p[i].burst_time;
    }
    pthread_exit(NULL);
}

void *sjf(void *processes) {
    struct Process *p = (struct Process *) processes;
    int n = sizeof(p) / sizeof(p[0]);
    int wait_time = 0;
    for (int i = 0; i < n; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].burst_time < p[min_idx].burst_time) {
                min_idx = j;
            }
        }
        struct Process temp = p[min_idx];
        p[min_idx] = p[i];
        p[i] = temp;
        p[i].waiting_time = wait_time;
        wait_time += p[i].burst_time;
    }
    pthread_exit(NULL);
}

void *pri_np(void *processes) {
    struct Process *p = (struct Process *) processes;
    int n = sizeof(p) / sizeof(p[0]);
    int wait_time = 0;
    for (int i = 0; i < n; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].priority > p[max_idx].priority) {
                max_idx = j;
            }
        }
        struct Process temp = p[max_idx];
        p[max_idx] = p[i];
        p[i] = temp;
        p[i].waiting_time = wait_time;
        wait_time += p[i].burst_time;
    }
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process *processes = (struct Process *) malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].pid = i+1;
    }

    pthread_t threads[NUM_THREADS];
    pthread_create(&threads[0], NULL, fcfs, (void *) processes);
    pthread_create(&threads[1], NULL, sjf, (void *) processes);
    pthread_create(&threads[2], NULL, pri_np, (void *) processes);

for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
}

int max_wait_time = INT_MIN;
int max_wait_time_pid = -1;
for (int i = 0; i < n; i++) {
    if (processes[i].waiting_time > max_wait_time) {
        max_wait_time = processes[i].waiting_time;
        max_wait_time_pid = processes[i].pid;
    }
}
if(max_wait_time_pid==1){
    printf("Process with longest waiting time is FCFS and has PID: %d\n", max_wait_time_pid);
}
else if(max_wait_time_pid==2){
    printf("Process with longest waiting time is SJF and has PID: %d\n", max_wait_time_pid);
}
else{
printf("Process with longest waiting time is PBS and has PID: %d\n", max_wait_time_pid);
}
free(processes);

return 0;
}
