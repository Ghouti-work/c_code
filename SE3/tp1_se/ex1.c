#include <stdio.h> //pour printf()
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> //pour fork()
void main() {
  int i;
  i = 1;
  while (i <= 10) {
    printf("TP LINUX\n");
    sleep(5);
    i = i + 1;
  }
}
