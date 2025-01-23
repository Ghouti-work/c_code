#include <pthread.h>
#include <stdio.h>

int V = 0;

void *increment(void *arg) {
  for (int i = 0; i < 10000; i++) {
    V++;
  }
  return NULL;
}

int main() {
  pthread_t th1, th2;

  pthread_create(&th1, NULL, increment, NULL);
  pthread_create(&th2, NULL, increment, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("Valeur finale de V : %d\n", V);
  return 0;
}
