#include <stdio.h>
#include <stdlib.h>

typedef struct PCB{
    int procId;
    int cpuBurst;
    int waitingTime;
    struct PCB *next;
    struct PCB *prev;
}PCB;

PCB *head = NULL;
int wTime = 0;

void addProcess(int PID, int CB) //CB - CPU Burst
{
    PCB *node = (PCB*) malloc (sizeof(PCB));
    node -> procId = PID;
    node -> cpuBurst = CB;
    node -> next = node -> prev = NULL;
    node -> waitingTime = wTime;
    wTime += CB;

    if (head == NULL)
    {
        head = node;
    }
    else
    {
        PCB *curr = head;
        while(curr -> next != NULL) {curr = curr -> next;}
        curr -> next = node;
        node -> prev = curr;
    }
    printf("\nProcess created\n");
}

void removeProcess()
{
    if (head != NULL)
    {
        printf("\nDeleted Process: %d\n", head -> procId);
        PCB *temp = head;
        head = head -> next;
        temp -> next = NULL;
        head -> prev = NULL;
        free(temp);
        temp = NULL;
    }
}

void displayProcess()
{
    PCB *temp = head;
    while(temp != NULL)
    {
        printf("\nPID: %d\tCPU Burst Time: %d\tWaiting Time: %d", temp -> procId, temp -> cpuBurst, temp -> waitingTime);
        temp = temp -> next;
    }
}

void averageTime()
{
    double avgWaiting = 0.0, avgTurnaround = 0.0, numTerms = 0.0;
    PCB *temp = head;
    while(temp != NULL)
    {
        avgWaiting += temp -> waitingTime;
        avgTurnaround += (temp -> waitingTime) + (temp -> cpuBurst);
        temp = temp -> next;
        numTerms = numTerms + 1.0;
    }
    avgWaiting /= numTerms;
    avgTurnaround /= numTerms;
    printf("\nAvg. Waiting Time: %lf\tAvg. Turnaround Time: %lf", avgWaiting, avgTurnaround);
}

int main()
{
    printf("\nThis program implements CPU Scheduling as FCFS\n");

    int temp = 1;
    while (temp != 0)
    {
        printf("\nEnter option:\n0. Exit\n1. Add a process\n2. Delete a process\n3. View processes\n4. Average Waiting Time\n");
        int choice;
        scanf("%d", &choice);

        switch(choice)
        {
            case 0:
                temp = 0; break;
            
            case 1:
            {
                int PID, CB;
                printf("\nEnter process ID and CPU Burst Time: ");
                scanf("%d %d", &PID, &CB);
                addProcess(PID, CB); break;
            }

            case 2:
                removeProcess(); break;
            
            case 3:
                displayProcess(); break;

            case 4:
                averageTime(); break;
            
            default:
                printf("\nInvalid Input"); break;
        }
    }
    return 0;
}
