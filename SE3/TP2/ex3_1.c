#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semStar; 
sem_t semHash; 

void *etoile(void *inutilise) {
    for (int i = 0; i < 150; i++){
        sem_wait(&semStar); 
        write(1, "*", 1);
        sem_post(&semHash); 
    }
    return NULL;
}

void *diese(void *inutilise) {
    for (int i = 0; i < 150; i++) { 
        sem_wait(&semHash); 
        write(1, "#", 1);
        sem_post(&semStar); 
    }
    return NULL;
}

int main(void) {
    pthread_t thrEtoile, thrDiese;

    sem_init(&semStar, 0, 1); 
    sem_init(&semHash, 0, 0); 

    printf("Je vais créer et lancer 2 threads\n");

    pthread_create(&thrEtoile, NULL, etoile, NULL);
    pthread_create(&thrDiese, NULL, diese, NULL);

    pthread_join(thrEtoile, NULL);
    pthread_join(thrDiese, NULL);

    printf("\nLes 2 threads se sont termines\n");
    printf("Fin du thread principal\n");

    sem_destroy(&semStar);
    sem_destroy(&semHash);

    return EXIT_SUCCESS;
}

