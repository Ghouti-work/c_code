#include <stdio.h>

#include <pthread.h>

#include <stdlib.h>

void *fct1()

{

  printf("lmd \n");
}

void *fct2()

{

  printf("s5\n");
}

void *fct3()

{

  printf("informatique \n");
}

int main()

{

  pthread_t tid1, tid2, tid3;

  pthread_create(&tid1, NULL, fct1, NULL);

  pthread_create(&tid2, NULL, fct2, NULL);

  pthread_create(&tid3, NULL, fct3, NULL);

  pthread_join(tid1, NULL);

  pthread_join(tid2, NULL);

  pthread_join(tid3, NULL);

  return 0;
}
