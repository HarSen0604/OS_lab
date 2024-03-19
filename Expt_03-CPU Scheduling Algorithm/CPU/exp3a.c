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
	int waitingTime;
	struct PCB *next,*prev;
}pcb;

int main()
{
	pcb *head = (pcb *) malloc(sizeof(pcb));
	int n,j,i,wait=0;
	float sum=0.0f;
	pcb *pre = (pcb *) malloc(sizeof(pcb));
	printf("Enter number of processes :");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		pcb *temp = (pcb *) malloc(sizeof(pcb));
		temp->prev = temp->next = NULL;
		printf("Enter procId :");
		scanf("%d",&(temp->procId));
		printf("Enter cpuBurst :");
		scanf("%d",&(temp->cpuBurst));
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
	pre = head;
	for(i=0;i<n;i++)
	{
		pre->waitingTime = wait;
		sum += wait;
		wait += pre->cpuBurst;
		pre = pre->next;
	}
	pre = head;
	for(i=0;i<n;i++)
	{
		printf("Currently executing process %d. Time is %d secs\n",pre->procId,pre->cpuBurst);
		printf("This process waited for %d secs\n",pre->waitingTime);
		sleep(pre->cpuBurst);
		printf("The turn around is %d secs\n",pre->waitingTime + pre->cpuBurst);
		pre->next->prev = pre->prev;
		pre->prev->next = pre->next;
		pre = pre->next;
	}
	printf("The average waiting time is %.2f secs\n",sum/n);
}
