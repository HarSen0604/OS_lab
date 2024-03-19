#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_N 1000000

int n, p = 1; // shared variables
pthread_mutex_t lock;

void john() {
    pthread_mutex_lock(&lock);
    if (p >= n) {
        pthread_mutex_unlock(&lock);
    }
    int x = rand() % 8 + 2; // choose a random factor
    p *= x;
    printf("John multiplied by %d and got %d\n", x, p);
    if (p >= n)
    {
        printf("John wins!\n");
        exit(EXIT_SUCCESS);
    }
    pthread_mutex_unlock(&lock);
}

void michael() {
    
    pthread_mutex_lock(&lock);
    if (p >= n) {
        pthread_mutex_unlock(&lock);
        return;
    }
    int x = rand() % 8 + 2; // choose a random factor
    p *= x;
    printf("Michael multiplied by %d and got %d\n", x, p);
    if (p >= n)
    {
        printf("Michael wins!\n");
        exit(EXIT_SUCCESS);
    }
    pthread_mutex_unlock(&lock);
}

int main() {
    pid_t pid;
    printf("Enter a positive integer N: ");
    scanf("%d", &n);
    if (n <= 1 || n > MAX_N) {
        printf("Invalid input!\n");
        return 1;
    }
    srand(time(NULL)); // initialize the random seed
    pthread_mutex_init(&lock, NULL); // initialize the mutex lock
    pid = fork(); // create child process
    if (pid == 0) { // child process represents Michael
        michael();
    } else if (pid > 0) { // parent process represents John
        john();
        wait(NULL);
    } else { // error creating child process
        printf("Error creating child process!\n");
        return 1;
    }
    pthread_mutex_destroy(&lock); // destroy the mutex lock
    return 0;
}
