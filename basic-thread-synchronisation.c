#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREADS 5
sem_t semaphore;
void *thread_function(void *arg) {
    int id = *(int*)arg;
    printf("Thread %d is trying to enter critical section\n", id);
    sem_wait(&semaphore);
    printf("Thread %d entered critical section\n", id);
    sleep(1);
    printf("Thread %d is leaving critical section\n", id);
    sem_post(&semaphore);
    pthread_exit(NULL);
}
int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    sem_init(&semaphore, 0, 1);
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore);
    return 0;
}
