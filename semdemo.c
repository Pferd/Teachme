#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *functionA();
void *functionB();
void *functionC();

sem_t sem;

int main() {
    // initialize semaphore to 1
    sem_init(&sem, 1, 1);

    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, &functionA, NULL);
    pthread_create(&thread2, NULL, &functionB, NULL);
    pthread_create(&thread3, NULL, &functionC, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}

void criticalResource(char c) {
    int i, time;
    for (i = 0; i < 3; i++) {

        // P operation
        if (sem_wait(&sem) == 0) {

            // generate random amount of time)
            time = (int) ((double) rand() / RAND_MAX * 30);

            printf("Thread %c enters and sleeps for %d seconds...\n", c, time);

            sleep(time);

            printf("Thread %c leaves the critical section\n", c);

            // V operation
            sem_post(&sem);
        }
    }
}

void *functionA() {
    // thread A
   criticalResource('A');

    return 0;
}

void *functionB() {
    // thread B
criticalResource('B');
    return 0;
}

void *functionC() {
    // thread C
    criticalResource('C');

    return 0;
}
