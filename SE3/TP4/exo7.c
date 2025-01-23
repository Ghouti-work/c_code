#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 3

int NbL = 0; 

sem_t Redact; 
sem_t mutex;  
sem_t lect;    

void *lecteur(void *num);
void *redacteur(void *num);

int main() {
    int i;
    int numred[N] = {0, 1, 2};
    int numlec[N] = {0, 1, 2};

    pthread_t red[N];
    pthread_t lec[N];

  
    sem_init(&Redact, 0, 1); 
    sem_init(&mutex, 0, 1);   
    sem_init(&lect, 0, 1);    

 
    for (i = 0; i < N; i++) {
        pthread_create(&red[i], NULL, redacteur, &(numred[i]));
        pthread_create(&lec[i], NULL, lecteur, &(numlec[i]));
    }

      for (i = 0; i < N; i++) {
        pthread_join(red[i], NULL);
        pthread_join(lec[i], NULL);
    }

    printf("Fin des threads\n");
    return 0;
}


void *lecteur(void *num) {
    int i = *((int *)num);
 int j=0;
    while (j < N) {
        
        sem_wait(&lect);          
        sem_wait(&mutex);         

        NbL++;  // Un lecteur arrive
        if (NbL == 1) {
            // Si  premier lecteur, empecher les red d'entrer
            sem_wait(&Redact);
        }

        sem_post(&mutex);         // Libérer l'accès à NbL

        
        printf("Lecteur %d lit le fichier. Nous sommes maintenant %d lecteurs.\n", i, NbL);
        sleep(1); 

      
        sem_wait(&mutex);         
        NbL--;  
        if (NbL == 0) {
            sem_post(&Redact);
        }

        sem_post(&mutex);         // Libérer l'accès à NbL
        sem_post(&lect);          // Permettre à d'autres lecteurs d'entrer

        sleep(1); 
        j++;
    }

    return NULL;
}


void *redacteur(void *num) {
    int i = *((int *)num);
    int j=0;

    while (j < N) {
        
        sem_wait(&Redact);  // Un seul red a la fois
        
        
        printf("Rédacteur %d modifie le fichier.\n", i);
        sleep(1); 

        
        sem_post(&Redact);  
        
         
        j++;
    }

    return NULL;
}

