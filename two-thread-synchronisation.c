/*Write a program to synchronize two threads that work on a shared variable X, where one thread increments the X, another thread decrements the value. Sequence should be increment followed by decrement always.*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
int X = 0;
sem_t increment_sem, decrement_sem;
void *increment_function(void *arg) {
    int i;
    for (i = 0; i < 5; i++) {
        sem_wait(&increment_sem);
        X++;
        printf("Incremented X to %d\n", X);
        sem_post(&decrement_sem);
    }
    pthread_exit(NULL);
}

void *decrement_function(void *arg) {
    int i;
    for (i = 0; i < 5; i++) {
        sem_wait(&decrement_sem);
        X--;
        printf("Decremented X to %d\n", X);
        sem_post(&increment_sem);
    }
    pthread_exit(NULL);
}

int main() {
    printf("Initial value of X: %d\n",X);
    pthread_t increment_thread, decrement_thread;

    sem_init(&increment_sem, 0, 1);
    sem_init(&decrement_sem, 0, 0);

    pthread_create(&increment_thread, NULL, increment_function, NULL);
    pthread_create(&decrement_thread, NULL, decrement_function, NULL);

    pthread_join(increment_thread, NULL);
    pthread_join(decrement_thread, NULL);

    sem_destroy(&increment_sem);
    sem_destroy(&decrement_sem);

    return 0;
}
