#include <pthread.h>
#include <stdio.h>

void *fct() {
  printf("lmd ");
  printf("informatique ");
  printf("s5\n");
  pthread_exit(NULL);
}

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, fct, NULL);

  pthread_join(tid, NULL);

  return 0;
}
