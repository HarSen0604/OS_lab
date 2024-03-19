#include <stdio.h>
#include <stdlib.h>

int main()
{
    int queue_size = 0, head = 0, total_head_movement = 0, diskSize = 0, movement = -1;

    printf("Enter the number of requests: ");
    scanf("%d", &queue_size);
    int request_queue[queue_size];

    printf("Enter the request queue: ");
    for (int i = 0; i < queue_size; i++)
        scanf("%d", &request_queue[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter the size of the disk: ");
    scanf("%d", &diskSize);
    diskSize--;

    printf("Enter the movement of the head. For high 1. For low 0: ");
    scanf("%d", &movement);

    for (int i = 0; i < queue_size; i++)
    {
        for (int j = 0; j < queue_size - 1 - i; j++)
        {
            if (request_queue[j] > request_queue[j+1])
            {
                int temp = request_queue[j];
                request_queue[j] = request_queue[j+1];
                request_queue[j+1] = temp;
            }
        }
    }

    printf("\nOrder: %d ", head);
    int index = -1;
    for (int i = 0; i < queue_size; i++)
    {
        if (request_queue[i] > head)
        {
            index = i;
            break;
        }
    }

    if (movement)
    {
        // move to the higher requests
        for (int i = index; i < queue_size; i++)
        {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
        total_head_movement += diskSize - head;

        // move back to the lower requests
        head = diskSize;
        printf("%d ", diskSize);
        for (int i = index - 1; i >= 0; i--)
        {
            total_head_movement += abs(head - request_queue[i]);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
    }
    else
    {
        // move to the lower requests
        for (int i = index - 1; i >= 0; i--)
        {
            total_head_movement += abs(head - request_queue[i]);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
        total_head_movement += head;

        // move back to the higher requests
        head = 0;
        printf("%d ", head);
        for (int i = index; i < queue_size; i++)
        {
            total_head_movement += abs(request_queue[i] - head);
            printf("%d ", request_queue[i]);
            head = request_queue[i];
        }
    }

    printf("\nTotal head movement: %d cylinders\n", total_head_movement);
    return 0;
}
