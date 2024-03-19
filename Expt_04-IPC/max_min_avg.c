#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables
int average = 0;
int minimum = 0;
int maximum = 0;

// Define a function to calculate the average of a list of numbers
void *calculate_average(void *arg) {
    int *numbers = (int *) arg;
    int sum = 0;
    int count = numbers[0];
    for (int i = 1; i <= count; i++) {
        sum += numbers[i];
    }
    average = sum / count;
    pthread_exit(NULL);
}

// Define a function to determine the maximum value in a list of numbers
void *calculate_maximum(void *arg) {
    int *numbers = (int *) arg;
    int count = numbers[0];
    maximum = numbers[1];
    for (int i = 2; i <= count; i++) {
        if (numbers[i] > maximum) {
            maximum = numbers[i];
        }
    }
    pthread_exit(NULL);
}

// Define a function to determine the minimum value in a list of numbers
void *calculate_minimum(void *arg) {
    int *numbers = (int *) arg;
    int count = numbers[0];
    minimum = numbers[1];
    for (int i = 2; i <= count; i++) {
        if (numbers[i] < minimum) {
            minimum = numbers[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    // Parse input arguments
    int numbers[argc];
    numbers[0] = argc - 1;
    for (int i = 1; i < argc; i++) {
        numbers[i] = atoi(argv[i]);
    }

    // Create threads to calculate statistics
    pthread_t avg_thread, min_thread, max_thread;
    pthread_create(&avg_thread, NULL, calculate_average, numbers);
    pthread_create(&min_thread, NULL, calculate_maximum, numbers);
    pthread_create(&max_thread, NULL, calculate_minimum, numbers);
    
    pthread_join(avg_thread, NULL);
    pthread_join(min_thread, NULL);
    pthread_join(max_thread, NULL);

    // Print results
    printf("The average value is %d\n", average);
    printf("The minimum value is %d\n", minimum);
    printf("The maximum value is %d\n", maximum);

    return 0;
}
