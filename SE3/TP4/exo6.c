#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define N 3 // taille du tampon

int tampon[N];
int i = 0, j = 0;  
sem_t sem_prod, sem_cons; 
pthread_mutex_t mutex, mutex2; 

void* consommateur(void*);
void* producteur(void*);

int main()
{
    pthread_t th1, th2;

    
    sem_init(&sem_prod, 0, N); 
    sem_init(&sem_cons, 0, 0); 
   
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex2, NULL);

   
    pthread_create(&th1, NULL, &producteur, NULL);
    pthread_create(&th2, NULL, &consommateur, NULL);

   
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    
    sem_destroy(&sem_prod);
    sem_destroy(&sem_cons);
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex2);

    printf("Fin des threads et du programme principal.\n");
    return 0;
}

// Fonction producteur
void* producteur(void* depot)
{
    int nbprod = 0, mess = 0;

    do {
        
        sem_wait(&sem_prod);

        
        pthread_mutex_lock(&mutex);

        
        tampon[i] = mess;
        printf("\nProducteur : tampon[%d] = %d\n", i, mess);
        i = (i + 1) % N; 
        mess++; 
        nbprod++;

       
        pthread_mutex_unlock(&mutex);

        
        sem_post(&sem_cons);
        sleep(2);
       }while (nbprod < 5);

    return NULL;
}


void* consommateur(void* retrait)
{
    int nbcons = 0, mess;

    do {
                sem_wait(&sem_cons);

                pthread_mutex_lock(&mutex2);

                mess = tampon[j];
        printf("\nConsommateur : tampon[%d] = %d\n", j, mess);
        j = (j + 1) % N; 
        nbcons++;

        
        pthread_mutex_unlock(&mutex2);

                sem_post(&sem_prod);
                
        sleep(2);
    }while (nbcons < 5);

    return NULL;
}

