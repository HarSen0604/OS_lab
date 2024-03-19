#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PCB
{
    int procId;
    int cpuBurst;
    int waitingTime;
    struct PCB *next;
    struct PCB *prev;
}PCB;

PCB *head = NULL;
PCB *tail = NULL;

int wTime = 0;

void addProcess(int PID, int CB)
{
    PCB *temp = (PCB*) malloc (sizeof(PCB));
    temp -> procId = PID;
    temp -> cpuBurst = CB;
    temp -> waitingTime = wTime;
    wTime += CB;
    temp -> next = temp -> prev = NULL;

    if (head == NULL)
    {
        head = tail = temp;
    }
    else
    {
        tail -> next = temp;
        temp -> prev = tail;
        tail = temp;
    }
    printf("\n\tProcess created!\n");
}

void removeProcess()
{
    if (head != NULL)
    {
        PCB* temp = head;
        printf("\n\tProcess %d removed!\n", temp -> procId);
        head = head -> next;
        if (head != NULL)
            head -> prev = NULL;
        if (temp == tail)
            tail = NULL;
        temp -> next = temp -> prev = NULL;
        free(temp);
        temp = NULL;
    }
}

void displayProcess()
{
    PCB *temp = head;
    while (temp != NULL)
    {
        printf("\nPID: %d\tCPU Burst Time: %d\tWaiting Time: %d", temp -> procId, temp -> cpuBurst, temp -> waitingTime);
        temp = temp -> next;
    }
    printf("\n");
}

void timeCalc()
{
    double avgWaiting = 0.0, avgTurnAround = 0.0, numTerms = 0.0;
    PCB *temp = head;
    while (temp != NULL)
    {
        avgTurnAround += (temp -> waitingTime) + (temp -> cpuBurst);
        avgWaiting += (temp -> waitingTime);
        numTerms = numTerms + 1.0;
        temp = temp -> next;
    }
    printf("\nAvg. Waiting Time: %lf\tAvg. Turnaround Time: %lf\n", avgWaiting/numTerms, avgTurnAround/numTerms);    
}

int main()
{
    bool finish = false;
    while (!finish)
    {
        printf("\nEnter option:\n0. Exit\n1. Add a process\n2. Delete a process\n3. View processes\n4. Average Waiting Time\n...");
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 0:
            {
                finish = true;
                break;
            }

            case 1:
            {
                int PID, CB;
                printf("\nEnter process ID and CPU Burst Time: ");
                scanf("%d %d", &PID, &CB);                
                addProcess(PID, CB);
                break;
            }

            case 2:
            {
                removeProcess();
                break;
            }

            case 3:
            {
                displayProcess();
                break;
            }

            case 4:
            {
                timeCalc();
                break;
            }

            default:
            {
                printf("Enter the correct option");
                break;
            }
        }
    }
    return 0;
}