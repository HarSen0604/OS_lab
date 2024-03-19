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
int wTime = 0, numProcess = 0;

void addProcess(int PID, int CB)
{
    PCB *temp = (PCB*) malloc (sizeof(PCB));
    temp -> procId = PID;
    temp -> cpuBurst = CB;
    temp -> waitingTime = 0;
    temp -> next = NULL;

    if (head == NULL)
    {
        head = temp;
        tail = temp;
        temp -> prev = NULL;
    }
    else
    {
        PCB *temp1 = head;
        while (temp1 != NULL && temp1 -> cpuBurst <= CB)
        {
            temp1 = temp1 -> next;
        }

        if (temp1 == NULL)
        {
            // insert at tail
            tail -> next = temp;
            temp -> prev = tail;
            tail = temp;
        }
        else
        {
            // insert before temp
            PCB *prev1 = temp1 -> prev;
            temp -> next = temp1;
            temp -> prev = prev1;
            temp1 -> prev = temp;
            if (prev1 == NULL)
            {
                // insert at head
                head = temp;
            }
            else
            {
                prev1 -> next = temp;
            }
        }
    }
    printf("\nProcess created!\n");
}

void waitingTimeCalc()
{
    PCB *temp = head;
    wTime = 0;
    for (int i = 0; temp != NULL; i++)
    {
        temp -> waitingTime = wTime;
        wTime += temp -> cpuBurst;
        temp = temp -> next;
    }
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
        numProcess--;
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
    double avgWaiting = 0.0, avgTurnAround = 0.0;
    PCB *temp = head;
    while (temp != NULL)
    {
        avgTurnAround += (temp -> waitingTime) + (temp -> cpuBurst);
        avgWaiting += (temp -> waitingTime);
        temp = temp -> next;
    }
    printf("\nAvg. Waiting Time: %lf\tAvg. Turnaround Time: %lf\n", avgWaiting/((double)numProcess), avgTurnAround/((double)numProcess));    
}

int main()
{
    printf("Enter the number of processes: ");
    scanf("%d", &numProcess);
    for (int i = 0; i < numProcess; i++)
    {
        int PID, CB;
        printf("\nEnter process ID, CPU Burst Time: ");
        scanf("%d %d", &PID, &CB);
        addProcess(PID, CB);
    }
    waitingTimeCalc();

    bool finish = true;
    while(finish)
    {
        printf("\nEnter option:\n0. Exit\n1. Delete a process\n2. View processes\n3. Average Waiting Time\n...");
        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
            case 0:
            {
                finish = false;
                break;
            }

            case 1:
            {
                removeProcess();
                break;
            }

            case 2:
            {
                waitingTimeCalc();
                displayProcess();
                break;
            }

            case 3:
            {
                waitingTimeCalc();
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