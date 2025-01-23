#include <pthread.h>
#include <stdio.h>

#define SIZE 3
int matrix[SIZE][SIZE] = {0};
int desir[2] = {0, 0};
int turn = 0;

void *increment_diagonal(void *arg) {
  for (int i = 0; i < 100; i++) {
    desir[0] = 1;
    turn = 1;
    while (desir[1] == 1 && turn == 1)
      ;
    for (int j = 0; j < SIZE; j++) {
      matrix[j][j]++;
    }
    desir[0] = 1;
  }
  return NULL;
}

void *decrement_diagonal(void *arg) {
  for (int i = 0; i < 100; i++) {
    desir[0] = 1;
    turn = 0;
    while (desir[1] == 1 && turn == 1)
      ;
    for (int j = 0; j < SIZE; j++) {
      matrix[j][j]--;
    }
    desir[0] = 1;
  }

  return NULL;
}

int main() {

  pthread_t th1, th2;

  pthread_create(&th1, NULL, increment_diagonal, NULL);
  pthread_create(&th2, NULL, decrement_diagonal, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("Final matrix:\n");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}
