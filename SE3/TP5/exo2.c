#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Variables globales
int MAX = 10;  
int count = 1;  

// Mutex et condition
pthread_mutex_t mutex;  
pthread_cond_t cond;  

// Fonction pour afficher les nombres pairs
void *pair(void *arg) {  
    while (count <= MAX) {  
        pthread_mutex_lock(&mutex);  
        
        // Attendre tant que le nombre n'est pas pair
        while (count % 2 != 0) {  
            pthread_cond_wait(&cond, &mutex);  
        }  

        if (count <= MAX) {  
            printf("%d ", count++);  
        }

        // Signaler l'autre thread
        pthread_cond_signal(&cond);  
        pthread_mutex_unlock(&mutex);  
    }  

    pthread_exit(0);  
}  

// Fonction pour afficher les nombres impairs
void *impair(void *arg) {  
    while (count <= MAX) {  
        pthread_mutex_lock(&mutex);  
        
        // Attendre tant que le nombre n'est pas impair
        while (count % 2 == 0) {  
            pthread_cond_wait(&cond, &mutex);  
        }  

        if (count <= MAX) {  
            printf("%d ", count++);  
        }

        // Signaler l'autre thread
        pthread_cond_signal(&cond);  
        pthread_mutex_unlock(&mutex);  
    }  

    pthread_exit(0);  
}  

int main() {  
    pthread_t thread1;  
    pthread_t thread2;  

    // Initialisation du mutex et de la condition
    pthread_mutex_init(&mutex, NULL);  
    pthread_cond_init(&cond, NULL);  

    // Création des threads
    pthread_create(&thread1, NULL, impair, NULL);  
    pthread_create(&thread2, NULL, pair, NULL);  

    // Attendre la fin des threads
    pthread_join(thread1, NULL);  
    pthread_join(thread2, NULL);  

    // Destruction du mutex et de la condition
    pthread_mutex_destroy(&mutex);  
    pthread_cond_destroy(&cond);  

    return 0;  
}  

