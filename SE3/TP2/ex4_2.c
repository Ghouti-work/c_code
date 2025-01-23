#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int T[6] = {3, 1, 4, 1, 5, 10};
int max, min;
long max_factorial, min_factorial;
long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    max = T[0];
    min = T[0];
    for (int i = 1; i < 6; i++) {
        if (T[i] > max) max = T[i];
        if (T[i] < min) min = T[i];
    }
    
    pid_t pid_max = fork();
    if (pid_max == 0) {
        max_factorial = factorial(max);
        printf("Max: %d, Factorial: %llu (from child process)\n", max, max_factorial);
        exit(max_factorial); 
    }

    pid_t pid_min = fork();
    if (pid_min == 0) {
        min_factorial = factorial(min);
        printf("Min: %d, Factorial: %llu (from child process)\n", min, min_factorial);
        exit(min_factorial); 
    }

    int status;
    waitpid(pid_max, &status, 0);
    max_factorial = WEXITSTATUS(status); 
    
    waitpid(pid_min, &status, 0);
    min_factorial = WEXITSTATUS(status); 
    
    long sum = max_factorial + min_factorial;
    printf("Sum of Factorials: %llu\n", sum);

    return 0;
}

