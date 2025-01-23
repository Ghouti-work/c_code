#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int turn = 1; // Contrôle

void *etoile(void *inutilise) {
    for (int i = 0; i < 200; i++) {
        pthread_mutex_lock(&mutex);
        while (turn != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        write(1, "*", 1);
        turn = 2; // Passe au tour de Diese
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *diese(void *inutilise) {
    for (int i = 0; i < 200; i++) {
        pthread_mutex_lock(&mutex);
        while (turn != 2) {
            pthread_cond_wait(&cond, &mutex);
        }
        write(1, "#", 1);
        turn = 3; // Passe au tour de Arobase
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *arobase(void *inutilise) {
    for (int i = 0; i < 200; i++) {
        pthread_mutex_lock(&mutex);
        while (turn != 3) {
            pthread_cond_wait(&cond, &mutex);
        }
        write(1, "@", 1);
        turn = 1; // Retourne au tour de Etoile
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void) {
    pthread_t thrEtoile, thrDiese, thrArobase;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    printf("Je vais créer et lancer 3 threads\n");
    pthread_create(&thrEtoile, NULL, etoile, NULL);
    pthread_create(&thrDiese, NULL, diese, NULL);
    pthread_create(&thrArobase, NULL, arobase, NULL);

    pthread_join(thrEtoile, NULL);
    pthread_join(thrDiese, NULL);
    pthread_join(thrArobase, NULL);

    printf("\nLes 3 threads se sont terminés\n");
    printf("Fin du thread principal\n");

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
