#include <stdio.h>
#include <stdlib.h>

typedef struct PCB
{
    int procId;
    int cpuBurst;
    int waitingTime;
    int arrivalTime;
    int perCBT;
    struct PCB *next;
    struct PCB *prev;
}PCB;

PCB *head = NULL;

int main()
{
    int numProcess = -1;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcess);

    PCB *prev1 = NULL;
    for (int i = 0; i < numProcess; i++)
    {
        PCB *temp = (PCB*) malloc (sizeof(PCB));
        temp -> procId = i;
        printf("\nEnter the CPU Burst: ");
        scanf("%d", &temp -> cpuBurst);
        temp -> perCBT = temp -> cpuBurst;
        printf("Enter the arrival time: ");
        scanf("%d", &temp -> arrivalTime);
        temp -> waitingTime = 0;
        temp -> next = temp -> prev = NULL;

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            prev1 -> next = temp;
            temp -> prev = prev1;
        }
        prev1 = temp;
    }
    prev1 -> next = head;
    head -> prev = prev1;

    int num1 = numProcess, total_time = 0;
    float total_wait = 0.0f, total_turn = 0.0f;
    while (num1 != 0)
    {
        PCB *temp = head;
        PCB *small = head;

        while (small -> cpuBurst == 0)
        {
            small = small -> next;
        }
        for (int i = 0; i < numProcess; i++)
        {
            if ((temp -> cpuBurst > 0) && (temp -> cpuBurst < small -> cpuBurst) && (temp -> arrivalTime <= total_time))
            {
                small = temp;
            }
            temp = temp -> next;
        }
        small -> cpuBurst--;
        total_time++;

        if (small -> cpuBurst == 0)
        {
            small -> waitingTime = total_time - small -> perCBT - small -> arrivalTime;
            if (small -> waitingTime < 0)
            {
                small -> waitingTime = 0;
            }
            total_wait += small -> waitingTime;
            total_turn += small -> waitingTime + small -> perCBT;
            printf("P%d finished running. Waiting time: %d\n", small -> procId, small -> waitingTime);
            num1--;
        }
    }
    printf("\nAvg. waiting time: %f", total_wait/numProcess);
    printf("\nAvg. turn around time: %f", total_turn/numProcess);
    return 0;
}