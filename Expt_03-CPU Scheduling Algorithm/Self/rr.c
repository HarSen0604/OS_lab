#include <stdio.h>
#include <stdlib.h>

typedef struct PCB
{
    int procId;
    int cpuBurst;
    int waitingTime;
    int arrivalTime;
    struct PCB *next;
    struct PCB *prev;
}PCB;

PCB *head = NULL;

void addProcess (PCB *temp)
{
    if (head == NULL)
    {
        head = temp;
        head -> next = head -> prev = head;
    }
    else
    {
        PCB *temp1 = head;
        while(temp1 -> next != head && (temp1 -> next -> arrivalTime) <= (temp -> arrivalTime))
        {
            temp1 = temp1 -> next;
        }
        temp -> next = temp1 -> next;
        temp -> prev = temp1;
        temp1 -> next -> prev = temp;
        temp1 -> next = temp;
    }
}

void displayProcess()
{
    PCB *temp1 = head;
    printf("\nPID\tCPU Burst\tArrival Time");
    do
    {
        printf("\n%d\t%d\t%d", temp1 -> procId, temp1 -> cpuBurst, temp1 -> arrivalTime);
    }while(temp1 != head);
    printf("\n---------------------------------\n");
}

void removeProcess(PCB *temp)
{
    PCB *temp1 = head;
    while(temp1 -> next != temp)
    {
        temp1 = temp1 -> next;
    }
    temp1 -> next = temp -> next;
    temp -> next -> prev = temp1;
    if (temp == head)
    {
        head = temp -> next;
        head -> prev = temp1;
    }
    temp->prev = temp->next = NULL;
}

int main()
{
    int numProcesses = -1;
    double total_wait = 0.0;
    int clock = 0, quantum = -1;

    printf("Enter the number of processes and time quantum: ");
    scanf("%d %d", &numProcesses, &quantum);

    printf("\n");
    for (int i = 0; i < numProcesses; i++)
    {
        PCB *temp = (PCB*) malloc (sizeof(PCB));
        printf("Enter the arrival time: ");
        scanf("%d", &temp -> arrivalTime);
        printf("Enter the CPU Burst: ");
        scanf("%d", &temp -> cpuBurst);
        temp -> waitingTime = 0;
        temp -> procId = i;
        addProcess(temp);
        printf("Process added\n");
    }

    displayProcess();

    while ((head != NULL) && (head -> arrivalTime >= 0 && head -> cpuBurst > 0))
    {
        displayProcess();
        PCB *temp1 = head;
        do
        {
            if (temp1 -> cpuBurst >= 0 && temp1 -> arrivalTime <= clock)
            {
                break;
            }
            temp1 = temp1 -> next;
        } while (temp1 != head);

        if (temp1 -> cpuBurst <= quantum)
        {
            temp1 -> waitingTime += clock - (temp1 -> arrivalTime);
            clock += temp1 -> cpuBurst;
            temp1 -> cpuBurst = 0;
            total_wait += (double)(temp1 -> waitingTime);
            removeProcess(temp1);
            printf("...P%d: (Wait: %d units)\n", temp1 -> procId, temp1 -> waitingTime);
            free(temp1);
            temp1 = NULL;
        }
        else if (temp1 -> cpuBurst > quantum)
        {
            removeProcess(temp1);
            temp1 -> waitingTime += clock - (temp1 -> arrivalTime);
            temp1 -> arrivalTime = clock + quantum;
            temp1 -> cpuBurst -= quantum;
            clock += quantum;
            addProcess(temp1);
        }
        else 
        {
            clock++;
        }
    }
    printf("\n\nAverage waiting time: %lf", total_wait/(double)(numProcesses));
    printf("\nAverage turn around time: %lf", (total_wait + (double)(clock))/(double)(numProcesses));
    return 0;
}