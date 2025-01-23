#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // pour sleep

// Variables globales
int nh = 0; // Nombre d'hommes dans la piscine
int nf = 0; // Nombre de femmes dans la piscine

// Mutex et conditions
pthread_mutex_t mutex;  
pthread_cond_t cond_home;  
pthread_cond_t cond_femme;  

// Fonction pour l'entrée des hommes
void *entrer_home(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);
    
    // Attendre si des femmes sont dans la piscine
    while (nf > 0) {
        pthread_cond_wait(&cond_home, &mutex);
    }
    
    nh++; // Incrémenter le nombre d'hommes
    printf("Homme %d entre dans la piscine.\n", id);
    
    pthread_mutex_unlock(&mutex);

    // Simuler une utilisation de la piscine
    sleep(4);

    pthread_mutex_lock(&mutex);
    
    nh--; // Décrémenter le nombre d'hommes
    printf("Homme %d sort de la piscine.\n", id);

    // Si plus aucun homme, signaler aux femmes
    if (nh == 0) {
        pthread_cond_broadcast(&cond_femme);
    }
    
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Fonction pour l'entrée des femmes
void *entrer_femme(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);
    
    // Attendre si des hommes sont dans la piscine
    while (nh > 0) {
        pthread_cond_wait(&cond_femme, &mutex);
    }
    
    nf++; // Incrémenter le nombre de femmes
    printf("Femme %d entre dans la piscine.\n", id);
    
    pthread_mutex_unlock(&mutex);

    // Simuler une utilisation de la piscine
    sleep(4);

    pthread_mutex_lock(&mutex);
    
    nf--; // Décrémenter le nombre de femmes
    printf("Femme %d sort de la piscine.\n", id);

    // Si plus aucune femme, signaler aux hommes
    if (nf == 0) {
        pthread_cond_broadcast(&cond_home);
    }
    
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[4];
    int ids[4] = {1, 2, 1, 2};

    // Initialiser le mutex et les conditions
    pthread_mutex_init(&mutex, NULL);  
    pthread_cond_init(&cond_home, NULL);  
    pthread_cond_init(&cond_femme, NULL);  

    // Création des threads pour les hommes et les femmes
    pthread_create(&threads[0], NULL, entrer_home, &ids[0]); // Homme 1
    pthread_create(&threads[1], NULL, entrer_home, &ids[1]); // Homme 2
    pthread_create(&threads[2], NULL, entrer_femme, &ids[2]); // Femme 1
    pthread_create(&threads[3], NULL, entrer_femme, &ids[3]); // Femme 2

    // Attendre la fin des threads
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Détruire le mutex et les conditions
    pthread_mutex_destroy(&mutex);  
    pthread_cond_destroy(&cond_home);  
    pthread_cond_destroy(&cond_femme);  

    return 0;
}

