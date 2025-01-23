#include <pthread.h>
#include <stdio.h>

int V = 0;
int c[2] = {0, 0};
int turn = 0;

void *peterson_increment(void *arg) {
  int i = *(int *)arg;
  for (int j = 0; j < 10000; j++) {
    c[i] = 1;
    turn = 1 - i;
    while (c[1 - i] == 1 && turn == 1 - i)
      ;
    V++;
    c[i] = 0;
  }
  return NULL;
}

int main() {
  pthread_t th1, th2;
  int id1 = 0, id2 = 1;

  pthread_create(&th1, NULL, peterson_increment, &id1);
  pthread_create(&th2, NULL, peterson_increment, &id2);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("Final value of V: %d\n", V);
  return 0;
}
