#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0
#define T 6

int cpt = 0;
sem_t sem1, sem2; // Déclaration des sémaphores

void* f0(void* arg);
void* f1(void* arg);

void* f0(void* arg) {
    int i;
    while (TRUE) {
        // Attente du sémaphore pour permettre à f0 de s'exécuter
        sem_wait(&sem1); 

        printf("<<Je suis le thread 1\n");
        for (i = 1; i <= 3; i++) {
            printf("\tA");
        }
        printf("\n");

        cpt++;
        if (cpt >= T) {
            exit(0);  // Terminer le programme après T itérations
        }

        // Libération du sémaphore pour permettre au thread f1 de s'exécuter
        sem_post(&sem2); 
    }
    return NULL;
}

void* f1(void* arg) {
    int i;
    while (TRUE) {
        // Attente du sémaphore pour permettre à f1 de s'exécuter
        sem_wait(&sem2); 

        printf(">>Je suis le thread 2\n");
        for (i = 4; i <= 6; i++) {
            printf("\tB");
        }
        printf("\n");

        cpt++;
        if (cpt >= T) {
            exit(0);  // Terminer le programme après T itérations
        }

        // Libération du sémaphore pour permettre au thread f0 de s'exécuter
        sem_post(&sem1); 
    }
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t thread0, thread1;

    // Initialisation des sémaphores
    sem_init(&sem1, 0, 0);  // sem1 commence à 1 pour permettre au thread f0 de commencer
    sem_init(&sem2, 0, 1);  // sem2 commence à 0 pour bloquer le thread f1

    // Création des threads
    pthread_create(&thread0, NULL, &f0, NULL);
    pthread_create(&thread1, NULL, &f1, NULL);

    // Attente que tous les threads soient terminés
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);

    // Destruction des sémaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}

//le probleme c'est que le thread 1 et le seul qui s'execute

