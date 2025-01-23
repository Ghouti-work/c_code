#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *etoile(void *inutilise) {
    for (int i = 0; i < 10; i++) { 
        write(1, "*", 1);
    }
    return NULL;
}

void *diese(void *inutilise) {
    for (int i = 0; i < 10; i++) { 
        write(1, "#", 1);
    }
    return NULL;
}

int main(void) {
    pthread_t thrEtoile, thrDiese;

    printf("Je vais créer et lancer 2 threads\n");

    pthread_create(&thrEtoile, NULL, etoile, NULL);
    pthread_create(&thrDiese, NULL, diese, NULL);

    pthread_join(thrEtoile, NULL);
    pthread_join(thrDiese, NULL);

    printf("\nLes 2 threads se sont termines\n");
    printf("Fin du thread principal\n");

    return EXIT_SUCCESS;
}

