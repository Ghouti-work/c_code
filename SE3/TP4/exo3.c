#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Déclaration des sémaphores
sem_t sem_t2, sem_t3, sem_t1;

void *T1(void *arg) {
    // Attendre que T3 ait fini son affichage
    sem_wait(&sem_t1); // T1 attend que T3 ait terminé

 
    printf("2");
    printf("0");
    printf("1");
    printf("9\n");

    pthread_exit(NULL);
}

void *T2(void *arg) {
    // Affichage "SYS"
    printf("S");
    printf("Y");
    printf("S");

    // Signaler à T3 qu'il peut s'exécuter
    sem_post(&sem_t3);

    pthread_exit(NULL);
}

void *T3(void *arg) {
    // Attendre que T2 ait terminé son affichage
    sem_wait(&sem_t3); // T3 attend que T2 ait terminé

    
    printf("T");
    printf("E");
    printf("M");
    printf("E\n");

    // Signaler à T1 qu'il peut s'exécuter
    sem_post(&sem_t1);

    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2, tid3;

    // Initialiser les sémaphores
    sem_init(&sem_t2, 0, 0);  // T2 peut démarrer directement
    sem_init(&sem_t3, 0, 0);  // T3 est bloqué au début
    sem_init(&sem_t1, 0, 0);  // T1 est bloqué au début

   
    pthread_create(&tid1, NULL, T1, NULL);
    pthread_create(&tid2, NULL, T2, NULL);
    pthread_create(&tid3, NULL, T3, NULL);

    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // Détruire les sémaphores
    sem_destroy(&sem_t2);
    sem_destroy(&sem_t3);
    sem_destroy(&sem_t1);

    exit(0);
}

