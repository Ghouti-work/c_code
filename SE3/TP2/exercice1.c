#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem1;
sem_t sem2;

void *fct1() {
    printf("lmd ");
    sem_post(&sem1); 
    return NULL;
}

void *fct2() {
    sem_wait(&sem1); 
    printf("informatique ");
    sem_post(&sem2); 
    return NULL;
}

void *fct3() {
    sem_wait(&sem2); 
    printf("s5\n");
    return NULL;
}

int main() {
    pthread_t tid1, tid2, tid3;

    sem_init(&sem1, 0, 0); 
    sem_init(&sem2, 0, 0); 

    pthread_create(&tid1, NULL, fct1, NULL);
    pthread_create(&tid2, NULL, fct2, NULL);
    pthread_create(&tid3, NULL, fct3, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}

