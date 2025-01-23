#include <pthread.h>
#include <stdio.h>

int a = 0;                  
pthread_mutex_t mutex;      // Mutex pour protéger l'accès à 'a'

void* increment(void* arg);
void* decrement(void* arg);

int main() {
    pthread_t threadA, threadB;

    // Initialisation du mutex
    pthread_mutex_init(&mutex, NULL);

    printf("programme principal : a = %d\n", a);

  
    pthread_create(&threadA, NULL, increment, NULL);
    pthread_create(&threadB, NULL, decrement, NULL);

    
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    
    printf("programme principal, fin threads : a = %d\n", a);

    // Destruction du mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

void* increment(void* arg) {
    pthread_mutex_lock(&mutex);  // Verrouille le mutex avant de modifier 'a'
    a = a + 1;
    printf("thread A increment : a = %d\n", a);
    pthread_mutex_unlock(&mutex);  // Déverrouille le mutex après modification
    return NULL;
}

void* decrement(void* arg) {
    pthread_mutex_lock(&mutex);  // Verrouille le mutex avant de modifier 'a'
    a = a - 1;
    printf("thread B decrement : a = %d\n", a);
    pthread_mutex_unlock(&mutex);  // Déverrouille le mutex après modification
    return NULL;
}

//probleme:race condition. Cela se produit parce que les deux threads (threadA et threadB) accèdent à la variable partagée a simultanément sans aucune protection.
//Solution avec un sémaphore: exclusion mutuelle


