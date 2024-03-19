#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

typedef struct PCB
{
	int procId;
	int cpuBurst;
	int burstDouble;
	int waitingTime;
	int turnAroundTime;
	struct PCB *next,*prev;
}pcb;

int main()
{
	pcb *head = (pcb *) malloc(sizeof(pcb));
	int n,i,quantum,tempvar,sum=0;
	float wait=0.0f;
	pcb *pre = (pcb *) malloc(sizeof(pcb));
	printf("Enter number of processes :");
	scanf("%d",&n);
	tempvar = n;
	for(i=0;i<n;i++)
	{
		pcb *temp = (pcb *) malloc(sizeof(pcb));
		temp->prev = temp->next = NULL;
		printf("Enter procId :");
		scanf("%d",&(temp->procId));
		printf("Enter cpuBurst :");
		scanf("%d",&(temp->cpuBurst));
		temp->burstDouble = temp->cpuBurst;
		if(i == 0)
		{
			head = temp;
		}
		else
		{
			pre->next = temp;
			temp->prev = pre;
		}
		pre = temp;
	}
	pre->next = head;
	head->prev = pre;
	printf("Enter time quantum :");
	scanf("%d",&quantum);
	pre = head;
	while(tempvar != 0)
	{
		if(pre->cpuBurst > quantum)
		{
			printf("Currently executing process %d. The time given is %d secs\n",pre->procId,quantum);
			sleep(quantum);
			sum += quantum;
			pre->cpuBurst -= quantum;
		}
		else if(pre->cpuBurst != 0)
		{
			printf("Currently executing process %d. The time given is %d secs\n",pre->procId,pre->cpuBurst);
			sleep(pre->cpuBurst);
			sum += pre->cpuBurst;
			pre->turnAroundTime = sum;
			pre->cpuBurst = 0;
			pre->waitingTime = sum - pre->burstDouble;
			tempvar--;
		}
		pre = pre->next;
	}
	printf("\nAll processes done executing :)\n\nTotal time elapsed is %d secs\n\n",sum);
	pre = head;
	for(i=0;i<n;i++)
	{
		wait += pre->waitingTime;
		printf("The waiting time of process %d is %d secs\n",pre->procId,pre->waitingTime);
		printf("The turn around time is %d secs\n",pre->turnAroundTime);
		pre = pre->next;
	}
	printf("The average waiting time is %.2f secs\n",wait/n);
}
