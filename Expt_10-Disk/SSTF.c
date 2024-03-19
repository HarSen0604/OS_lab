#include <stdio.h>
#include <stdlib.h>

int main() {
    int queue_size = 0, head = 0, total_head_movement = 0;

    printf("Enter queue size: ");
    scanf("%d", &queue_size);

    int queue[queue_size];
    printf("Enter the request queue: ");

    for (int i = 0; i < queue_size; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter intial head position: ");
    scanf("%d", &head);

    int distances[queue_size];

    for (int i = 0; i < queue_size; i++) {
        distances[i] = abs(queue[i] - head);
    }

    // sort distances and respective values
    for (int i = 0; i < queue_size; i++) {
        for (int j = 0; j < queue_size - i - 1; j++) {
            if (distances[j] > distances[j + 1]) {
                int temp1 = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp1;

                int temp2 = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp2;
            }
        }
    }

    total_head_movement += abs(queue[0] - head);

    printf("\nOrder: %d %d ", head, queue[0]);

    // normal scanning
    for (int i = 1; i < queue_size; i++) {
        total_head_movement += abs(queue[i] - queue[i - 1]);
        printf("%d ", queue[i]);
    }

    printf("\nTotal head movement is %d cylinders", total_head_movement);
    return 0;
}
