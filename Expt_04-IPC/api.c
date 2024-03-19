#include <stdio.h>
#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000
#define BITMAP_SIZE (MAX_PID - MIN_PID + 1)

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

int main() {
    if (allocate_map() == -1) {
        printf("Failed to allocate PID bitmap\n");
        return 1;
    }

    int pid1 = allocate_pid();
    int pid2 = allocate_pid();
    int pid3 = allocate_pid();

    printf("Allocated PIDs: %d %d %d\n", pid1, pid2, pid3);

    release_pid(pid2);

    int pid4 = allocate_pid();

    printf("Allocated new PID after releasing %d: %d\n", pid2, pid4);
    free(pid_bitmap);

    return 0;
}
