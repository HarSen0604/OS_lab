#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define MIN_PID 300
#define MAX_PID 5000
#define BITMAP_SIZE (MAX_PID - MIN_PID + 1)
int size = 0;

// Bitmap data structure to keep track of allocated PIDs
static unsigned char *pid_bitmap;

// Initialize the PID bitmap
int allocate_map(void) {
    pid_bitmap = malloc(BITMAP_SIZE * sizeof(unsigned char));
    if (pid_bitmap == NULL) {
        return -1;
    }
    return 1;
}

// Allocate a PID
int allocate_pid(void) {
    int pid = -1;
    for (int i = 0; i < BITMAP_SIZE; i++) {
        if (pid_bitmap[i] == 0) {
            pid_bitmap[i] = 1;
            pid = i + MIN_PID;
            break;
        }
    }
    return pid;
}

// Release a PID
void release_pid(int pid) {
    if (pid >= MIN_PID && pid <= MAX_PID) {
        pid_bitmap[pid - MIN_PID] = 0;
    }
}

//main process
void *test_thread(void *temp) {
    int pid = allocate_pid();
    int temp1 = (intptr_t) temp;
    printf("Thread %d: Allocated pid %d\n", temp1, pid);
    srand(time(NULL));
    int sleep_time = rand() % 10;
    sleep(sleep_time);
    release_pid(pid);
    printf("Thread %d: Released pid %d\n", temp1, pid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (allocate_map() == -1) {
        printf("Failed to allocate PID bitmap\n");
        return 1;
    }

    size = atoi(argv[1]);

    pthread_t demo[size];
    for (int i = 0; i < size; i++){
        pthread_create(&demo[i], NULL, test_thread, (void *)i);
    }
    for (int i = 0; i < size; i++){
        pthread_join(demo[i], NULL);
    }
    free(pid_bitmap);

    return 0;
}