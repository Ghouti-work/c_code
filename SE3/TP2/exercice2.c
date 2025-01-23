#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem1; 
sem_t sem2; 

void* fct1(void *arg) {
	printf("je suis le thread A \n"); 
    for (int i = 1; i <= 3; i++) {
        printf("A");
    }
    sem_post(&sem1); 
    printf("\n");
    return NULL;
}

void* fct2(void *arg) {
    sem_wait(&sem1); 
    printf("je suis le thread B \n"); 
    for (int i = 1; i <= 3; i++) {
        printf("B");
    }
    sem_post(&sem2);
    printf("\n");
    return NULL;
}

void* fct3(void *arg) {
    sem_wait(&sem2); 
    printf("je suis le thread C \n"); 
    for (int i = 1; i <= 3; i++) {
        printf("C");
    }
    printf("\n");
    return NULL;
}

int main() {
    pthread_t threadA, threadB, threadC;

    sem_init(&sem1, 0, 0); 
    sem_init(&sem2, 0, 0); 

    printf("debut execution de mes threads\n");

    pthread_create(&threadA, NULL, fct1, NULL);
    pthread_create(&threadB, NULL, fct2, NULL);
    pthread_create(&threadC, NULL, fct3, NULL);
	
	pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    printf("\nfin de mes threads\n");

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}

