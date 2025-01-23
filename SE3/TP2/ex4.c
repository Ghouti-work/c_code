#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 6

int T[SIZE] = {3, 1, 4, 1, 5, 9}; 
int max, min;
long max_factorial, min_factorial;

long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

void *calculate_max_factorial(void *arg) {
    max_factorial = factorial(max);
    return NULL;
}

void *calculate_min_factorial(void *arg) {
    min_factorial = factorial(min);
    return NULL;
}

int main() {
    pthread_t thread_max, thread_min;

    max = T[0];
    min = T[0];
    for (int i = 1; i < SIZE; i++) {
        if (T[i] > max) max = T[i];
        if (T[i] < min) min = T[i];
    }
    
    pthread_create(&thread_max, NULL, calculate_max_factorial, NULL);
    pthread_create(&thread_min, NULL, calculate_min_factorial, NULL);

   
    pthread_join(thread_max, NULL);
    pthread_join(thread_min, NULL);

    long sum = max_factorial + min_factorial;

    printf("Max: %d, Factorial: %llu\n", max, max_factorial);
    printf("Min: %d, Factorial: %llu\n", min, min_factorial);
    printf("Sum of Factorials: %llu\n", sum);

    return 0;
}

