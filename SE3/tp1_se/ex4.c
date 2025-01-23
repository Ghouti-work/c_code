#include <stdio.h> //pour printf()
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h> //pour fork()
int main() {
  printf("Bonjour \n");
  if (fork() == 0) {
    printf("Monsieur\n");
    exit(0);
  } else {
    printf("Madame\n");
    wait(NULL);
    exit(0);
  }
  return 0;
}
