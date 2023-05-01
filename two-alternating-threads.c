/*Create two threads Odd and Even where odd prints the odd number in “N” and even prints the even number in “N”. Use synchronisation technique so that the output is in proper sequence.
      Example: In N=10,
      Output: 1 2 3 4 5 6 7 8 9 10.
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
int N;
sem_t odd_sem, even_sem;
void *odd_function(void *arg) {
    int i;
    for (i = 1; i <= N; i += 2) {
        sem_wait(&odd_sem);
        printf("%d ", i);
        sem_post(&even_sem);
    }
    pthread_exit(NULL);
}
void *even_function(void *arg) {
    int i;
    for (i = 2; i <= N; i += 2) {
        sem_wait(&even_sem);
        printf("%d ", i);
        sem_post(&odd_sem);
    }
    pthread_exit(NULL);
}
int main() {
    pthread_t odd_thread, even_thread;
    printf("Enter the value of N: ");
    scanf("%d", &N);
    sem_init(&odd_sem, 0, 1);
    sem_init(&even_sem, 0, 0);
    pthread_create(&odd_thread, NULL, odd_function, NULL);
    pthread_create(&even_thread, NULL, even_function, NULL);
    pthread_join(odd_thread, NULL);
    pthread_join(even_thread, NULL);
    sem_destroy(&odd_sem);
    sem_destroy(&even_sem);
    return 0;
}
