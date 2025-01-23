#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pid = fork();
  if (pid == 0) { // the child process has a value of 0 for pid
    printf("I am the child process\n");
  } else { // the parent process has a value of the child's pid
    printf("I am the parent process\n");
  }
  int res = wait(NULL);
  printf("Process %d has finished", res);
  printf("Process %d has finished", pid);
  return 0;
}
