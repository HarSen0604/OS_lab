#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_requests, head, total_head_movement = 0;

    // get input from user
    printf("Enter the number of requests: ");
    scanf("%d", &num_requests);
    int request_queue[num_requests+1];

    printf("Enter the request queue: ");
    for (int i = 1; i <= num_requests; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // add initial head position to request queue
    request_queue[0] = head;

    // perform FCFS disk scheduling algorithm
    for (int i = 0; i < num_requests; i++) {
        total_head_movement += abs(request_queue[i+1] - request_queue[i]);
    }

    // print results
    printf("\nOrder: ");
    for (int i = 0; i < num_requests; i++) {
        printf("%d ", request_queue[i]);
    }
    printf("\n");

    printf("Total head movement: %d cylinders\n", total_head_movement);

    return 0;
}

/*
Enter the number of requests: 8
Enter the request queue: 98 183 37 122 14 124 65 67
Enter initial head position: 53

Order: 53 98 183 37 122 14 124 65 
Total head movement: 640 cylinders
*/