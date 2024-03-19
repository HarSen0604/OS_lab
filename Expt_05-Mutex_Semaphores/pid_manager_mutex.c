#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MIN_PID 300
#define MAX_PID 5000
#define NUM_THREADS 5

int *pid_map;
pthread_mutex_t lock;

int allocate_map(void) {
    pid_map = calloc((MAX_PID-MIN_PID+1), sizeof(int));
    if (pid_map == NULL) return -1;
    return 1;
}

int allocate_pid(void) {
    pthread_mutex_lock(&lock);
    int i, pid = -1;
    for (i = 0; i <= (MAX_PID-MIN_PID); i++) {
        if (pid_map[i] == 0) {
            pid_map[i] = 1;
            pid = i + MIN_PID;
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    return pid;
}

void release_pid(int pid) {
    pthread_mutex_lock(&lock);
    pid_map[pid - MIN_PID] = 0;
    pthread_mutex_unlock(&lock);
}

void *pid_thread(void *thread_id) {
    int pid, tid = *(int*)thread_id;
    pid = allocate_pid();
    if (pid == -1) {
        printf("Thread %d: No PID available\n", tid);
    } else {
        printf("Thread %d: Allocated PID %d\n", tid, pid);
        int sleep_time = rand() % 10;
        sleep(sleep_time);
        release_pid(pid);
        printf("Thread %d: Released PID %d\n", tid, pid);
    }
    pthread_exit(NULL);
}

int main() {
    int i, thread_id[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    srand(time(NULL));
    if (allocate_map() == -1) {
        printf("PID map allocation failed\n");
        return -1;
    }
    pthread_mutex_init(&lock, NULL);
    for (i = 0; i < NUM_THREADS; i++) {
        thread_id[i] = i+1;
        pthread_create(&threads[i], NULL, pid_thread, (void*)&thread_id[i]);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    free(pid_map);
    return 0;
}
