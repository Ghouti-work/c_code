/*#define s 3
int m[s][s] = {0};

int desire[2] = {0, 0};  
int tour = 0;            

void *increment_diagonal(void *arg) {
  int i = *(int *)arg;  

  for (int t = 0; t < 100; t++) {
    desire[i] = 1;          

    while (desire[1 - i] == 1 && tour == 1 - i) ;

    // Section critique 
    for (int j = 0; j < s; j++) {
      m[j][j]++;
    }

    desire[i] = 0;  
  }

  return NULL;
}

void *decrement_diagonal(void *arg) {
  int i = *(int *)arg;  

  for (int t = 0; t < 100; t++) {
    desire[i] = 1;         
    tour = 1 - i;         

    while (desire[1 - i] == 1 && tour == 1 - i) ;

    // Section critique 
    for (int j = 0; j < s; j++) {
      m[j][j]--;
    }

    desire[i] = 0;  // Sortie de la section critique
  }

  return NULL;
}

int main() {
  pthread_t th1, th2;
  int id1 = 0, id2 = 1;


  pthread_create(&th1, NULL, increment_diagonal, &id1);
  pthread_create(&th2, NULL, decrement_diagonal, &id2);

 
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);


  printf("Final matrix:\n");
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }

  return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Déclaration des sémaphores
sem_t sem1, sem2;

void *T1(void *arg) {
    
    printf("S");
    sem_post(&sem2);
    
    sem_wait(&sem1);
      printf("S");
    sem_post(&sem2);

 sem_wait(&sem1);
    printf("E");
 sem_post(&sem2);
 
   sem_wait(&sem1);
    printf("E\n");

    pthread_exit(NULL);
}

void *T2(void *arg) {
    sem_wait(&sem2);
    printf("Y");
    sem_post(&sem1);
 

  
    

    
    

   sem_wait(&sem2);
    printf("T");
   sem_post(&sem1);
   
sem_wait(&sem2);
    printf("M");
 sem_post(&sem1);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    // Initialiser les sémaphores
    sem_init(&sem1, 0, 0);  // T1 est bloqué au début, T2 commence après T1
    sem_init(&sem2, 0, 0);  // T2 attend que T1 affiche "S"
    

    // Créer les threads
    pthread_create(&tid1, NULL, T1, NULL);
    pthread_create(&tid2, NULL, T2, NULL);

    // Attendre la fin des threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Détruire les sémaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);
  

    exit(0);
}

