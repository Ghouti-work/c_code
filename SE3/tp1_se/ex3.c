#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
void main() {
  int id, i;
  for (i = 0; i < 2; i++) {
    if (fork() == 0) {
      printf("A\n");
      exit(0);
    }
  }
  wait(0);
  printf("B\n");
}
