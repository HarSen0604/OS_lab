#include <stdio.h>
#include <stdlib.h>

int main() {
    int queue_size, head = 0, diskSize = 0, movement = -1;
    int total_head_movement = 0;

    printf("Enter the number of requests: ");
    scanf("%d", &queue_size);
    int request_queue[queue_size];

    printf("Enter the request queue: ");
    for (int i = 0; i < queue_size; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter the size of the disk: ");
    scanf("%d", &diskSize);
    diskSize--;

    printf("Enter the movement of the head. For high 1. For low 0: ");
    scanf("%d", &movement);

    // Sort the request array
    for (int i = 0; i < queue_size; i++) {
        for (int j = 0; j < queue_size - i - 1; j++) {
            if (request_queue[j] > request_queue[j + 1]) {
                int temp = request_queue[j];
                request_queue[j] = request_queue[j + 1];
                request_queue[j + 1] = temp;
            }
        }
    }

    // Find the index of the initial head position
    int index;
    for (int i = 0; i < queue_size; i++) {
        if (request_queue[i] > head) {
            index = i;
            break;
        }
    }

    printf("\nOrder: %d ", head);
    // If movement is towards high value
    if (movement) {
        for (int i = index; i < queue_size; i++) {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }

        total_head_movement += abs(diskSize - head);
        head = 0;
        printf("%d %d ", diskSize, head);

        for (int i = 0; i < index; i++) {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
    }
    // If movement is towards low value
    else {
        for (int i = index - 1; i >= 0; i--) {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
        total_head_movement += abs(head - 0);
        head = diskSize;
        printf("%d %d ", 0, head);

        for (int i = queue_size - 1; i >= index; i--) {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
    }

    printf("\nTotal head movement: %d cylinders", total_head_movement);
    return 0;
}
