#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include<sys/types.h>

/*int V = 0;
void *increment(void *inutilise) ;
void *decrement(void *inutilise) ;


int main(void) {
    setbuf(stdout, NULL); 
    pthread_t th1, th2;

 
    pthread_create(&th1, NULL, increment, NULL);
    pthread_create(&th2, NULL, decrement, NULL);

    
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    
    printf("La valeur finale de V est : %d\n", V);
    
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}

void *increment(void *inutilise) {
    for (int i = 0; i < 10000; i++) {
        V++;     
    }
    return NULL;
}
void *decrement(void *inutilise) {
    for (int i = 0; i < 10000; i++) {
         V--;
    }
    return NULL;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2, sem3;

void *etoile(void *inutilise);
void *diese(void *inutilise);
void *arobase(void *inutilise);

int main(void) {
    pthread_t thrEtoile, thrDiese, thrArobase;

   
    sem_init(&sem1, 0, 1);  
    sem_init(&sem2, 0, 0);  
    sem_init(&sem3, 0, 0);  

    setbuf(stdout, NULL);

    printf("Je vais créer et lancer 3 threads\n");

    // Création des threads
    pthread_create(&thrEtoile, NULL, etoile, NULL);
    pthread_create(&thrDiese, NULL, diese, NULL);
    pthread_create(&thrArobase, NULL, arobase, NULL);

    //printf("J’attends la fin des 3 threads\n");

  
    pthread_join(thrEtoile, NULL);
    pthread_join(thrDiese, NULL);
    pthread_join(thrArobase, NULL);

    
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);

    printf("\nLes 3 threads se sont terminés\n");
    printf("Fin du thread principal\n");

    pthread_exit(NULL);
    return EXIT_SUCCESS;
}

void *etoile(void *inutilise) {
    int i;
    char c1 = '*';
    for (i = 1; i <= 200; i++) {
        sem_wait(&sem1);         
        write(1, &c1, 1);      
        sem_post(&sem2);         
    }
    return NULL;
}

void *diese(void *inutilise) {
    int i;
    char c1 = '#';
    for (i = 1; i <= 200; i++) {
        sem_wait(&sem2);         
        write(1, &c1, 1);       
        sem_post(&sem3);         
    }
    return NULL;
}

void *arobase(void *inutilise) {
    int i;
    char c1 = '@';
    for (i = 1; i <= 200; i++) {
        sem_wait(&sem3);         
        write(1, &c1, 1);       
        sem_post(&sem1);         
    }
    return NULL;
}

