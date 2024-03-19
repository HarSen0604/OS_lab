#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#define NUM_PROCESSES 5

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int range;
    printf("Enter the range of numbers to check for prime numbers: ");
    scanf("%d", &range);

    // Create child processes
    int i;
    pid_t pid;
    FILE* fp = fopen("primes.txt", "w");
    for (i = 0; i < NUM_PROCESSES; i++) {
        pid = fork();
        if (pid < 0) {
            printf("Error: fork failed\n");
            exit(-1);
        } else if (pid == 0) {
            // Child process
            int start = (range / NUM_PROCESSES) * i + 2;
            int end = (range / NUM_PROCESSES) * (i + 1) + 1;
            if (i == NUM_PROCESSES - 1) {
                end = range;
            }
            for (int j = start; j <= end; j++) {
                if (isPrime(j)) {
                    fprintf(fp, "%d\n", j);
                }
            }
            fclose(fp);
            exit(0);
        }
    }

    // Wait for child processes to finish
    int status;
    for (i = 0; i < NUM_PROCESSES; i++) {
        wait(&status);
    }

    printf("Done writing prime numbers to file.\n");
    return 0;
}
