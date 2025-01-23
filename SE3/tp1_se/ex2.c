#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
void main() {
  int id, i;
  fork();
  printf("A\n");
  if ((id = fork() == 0)) {
    printf("B\n");
    exit(0);
  }
  wait(0);
  printf("C\n");
}
