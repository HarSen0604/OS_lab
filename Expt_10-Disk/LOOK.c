#include <stdio.h>
#include <stdlib.h>

int main() {
    int queue_size, head, size, movement = -1, total_head_movement = 0;

    printf("Enter the number of requests: ");
    scanf("%d", &queue_size);
    int request_queue[queue_size];

    printf("Enter the request sequence: ");
    for (int i = 0; i < queue_size; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter the total disk size: ");
    scanf("%d", &size);

    printf("Enter the movement of the head. For high 1. For low 0: ");
    scanf("%d", &movement);
    
    // sort the request array
    for (int i = 0; i < queue_size; i++) {
        for (int j = 0; j < queue_size - i - 1; j++) {
            if (request_queue[j] > request_queue[j + 1]) {
                int temp = request_queue[j];
                request_queue[j] = request_queue[j + 1];
                request_queue[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < queue_size; i++) {
        if (head < request_queue[i]) {
            index = i;
            break;
        }
    }
   
    printf("\nOrder: %d ", head);
    // if movement is towards high value
    if (movement) {
        for (int i = index; i < queue_size; i++) {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
        for (int i = index - 1; i >= 0; i--) {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
    }
    // if movement is towards low value
    else {
        for (int i = index - 1; i >= 0; i--) {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
        for (int i = index; i < queue_size; i++) {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
    }
    printf("\nTotal head movement: %d cylinders", total_head_movement);
    return 0;
}
