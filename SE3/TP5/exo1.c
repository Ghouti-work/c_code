#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>


sem_t sem1, sem2;

void *T1(void *arg) {
    printf("TE");
    sem_post(&sem1); 
    pthread_exit(NULL);
}

void *T2(void *arg) {
    sem_wait(&sem1); 
    printf("ST ");
    sem_post(&sem2); 
    pthread_exit(NULL);
}

void *T3(void *arg) {
    sem_wait(&sem2); 
    printf("TP  N\u00b02\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2, tid3;

    
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

   
    pthread_create(&tid1, NULL, T1, NULL);
    pthread_create(&tid2, NULL, T2, NULL);
    pthread_create(&tid3, NULL, T3, NULL);

    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);


    sem_destroy(&sem1);
    sem_destroy(&sem2);

    exit(0);
}

