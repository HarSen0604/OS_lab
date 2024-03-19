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
	int remainingTime;
	int arrivalTime;
	int waitingTime;
	int turnAroundTime;
	struct PCB *next,*prev;
}pcb;

int n;
pcb *head;
pcb *pre;

void sort(int nn)
{
	int i,j;
	for(i=1;i<nn;i++)
	{
		pre = head;
		for(j=1;j<nn;j++)
		{
			if(pre->remainingTime > pre->next->remainingTime)
			{
				int temp1 = pre->cpuBurst;
				int temp2 = pre->procId;
				int temp3 = pre->arrivalTime;
				int temp4 = pre->remainingTime;
				pre->cpuBurst = pre->next->cpuBurst;
				pre->procId = pre->next->procId;
				pre->arrivalTime = pre->next->arrivalTime;
				pre->remainingTime = pre->next->remainingTime;
				pre->next->cpuBurst = temp1;
				pre->next->procId = temp2;
				pre->next->arrivalTime = temp3;
				pre->next->remainingTime = temp4;
			}
			pre = pre->next;
		}
	}
}

int main()
{
	int i,j,wait=0,m=2;
	float sum = 0.0f;
	printf("Enter number of processes :");
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++)
	{
		pcb *temp = (pcb *) malloc(sizeof(pcb));
		temp->prev = temp->next = NULL;
		printf("Enter procId :");
		scanf("%d",&(temp->procId));
		printf("Enter cpuBurst :");
		scanf("%d",&(temp->cpuBurst));
		temp->remainingTime = temp->cpuBurst;
		printf("Enter arrivalTime :");
		scanf("%d",&(temp->arrivalTime));
		arr[i] = temp->arrivalTime;
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
	for(i=1;i<n;i++)
	{
		pre = head;
		for(j=1;j<n;j++)
		{
			if(pre->arrivalTime > pre->next->arrivalTime)
			{
				int temp1 = pre->cpuBurst;
				int temp2 = pre->procId;
				int temp3 = pre->arrivalTime;
				int temp4 = pre->remainingTime;
				pre->cpuBurst = pre->next->cpuBurst;
				pre->procId = pre->next->procId;
				pre->arrivalTime = pre->next->arrivalTime;
				pre->remainingTime = pre->next->remainingTime;
				pre->next->cpuBurst = temp1;
				pre->next->procId = temp2;
				pre->next->arrivalTime = temp3;
				pre->next->remainingTime = temp4;
			}
			if(arr[j-1] > arr[j])
			{
				int temp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = temp;
			}
			pre = pre->next;
		}
	}
	pre = head;
	for(i=0;i<n-1;i++)
	{
		pre = head;
		int t = arr[i+1] - arr[i];
		while(t > 0)
		{
			if(pre->remainingTime > t)
			{
				sum += t;
				pre->remainingTime -= t;
				t = 0;
			}
			else if(pre->remainingTime < t && pre->remainingTime != 0)
			{
				int temp = pre->remainingTime;
				sum += pre->remainingTime;
				pre->waitingTime = sum - (pre->cpuBurst + pre->arrivalTime);
				pre->turnAroundTime = sum - pre->arrivalTime;
				pre->remainingTime = 0;
				t -= temp;
			}
			pre = pre->next;
		}
		sort(m);
		m++;
	}
	pre = head;
	for(i=0;i<n;i++)
	{
		if(pre->remainingTime != 0)
		{
			sum += pre->remainingTime;
			pre->turnAroundTime = sum - pre->arrivalTime;
			pre->remainingTime = 0;
			pre->waitingTime = sum - (pre->cpuBurst + pre->arrivalTime);
		}
		pre=pre->next;
	}
	pre = head;
	for(i=1;i<n;i++)
	{
		pre = head;
		for(j=1;j<n;j++)
		{
			if(pre->procId > pre->next->procId)
			{
				int temp1 = pre->cpuBurst;int temp2 = pre->procId;int temp3 = pre->arrivalTime;int temp4 = pre->remainingTime;int temp5 = pre->waitingTime;int temp6 = pre->turnAroundTime;
				pre->cpuBurst = pre->next->cpuBurst;pre->procId = pre->next->procId;pre->arrivalTime = pre->next->arrivalTime;pre->remainingTime = pre->next->remainingTime;
				pre->waitingTime = pre->next->waitingTime;pre->turnAroundTime = pre->next->turnAroundTime;
				pre->next->cpuBurst = temp1;pre->next->procId = temp2;pre->next->arrivalTime = temp3;pre->next->remainingTime = temp4;
				pre->next->waitingTime = temp5;pre->next->turnAroundTime = temp6;
			}
			pre = pre->next;
		}
	}
	pre = head;
	for(i=0;i<n;i++)
	{
		printf("Process Id :%d\nCPU Burst :%d\nWaiting Time :%d\nTurn Around Time :%d\n",pre->procId,pre->cpuBurst,pre->waitingTime,pre->turnAroundTime);
		pre = pre->next;
	}
}
