#include <stdio.h>
#include <stdlib.h>
struct PCB{
int procId;
int CPUBurst;
int waitingTime;
int arrivalTime;
int perCBT;
struct PCB* next;
struct PCB* prev;
};

int main(){
    int NOP,y,wt,tat,flag,sum=0,quant,k;
    float avg_wt = 0.0,avg_tat=0.0;
    printf("Enter the no. of process:");
    scanf("%d",&NOP);
    y=NOP;
    struct PCB* head=NULL;
    for(int i=1;i<=NOP;i++){
        struct PCB* n=(struct PCB*)malloc(sizeof(struct PCB));
        printf("Enter the CPUBurst time for processId [%d]:",i);
        scanf("%d",&k);
        n->CPUBurst=k;
        n->perCBT=n->CPUBurst;
        printf("Enter the Arrival time for processId [%d]:",i);
        scanf("%d",&k);
        n->arrivalTime=k;
        n->procId=i;
        if(head==NULL){
            head=n;
            n->next=NULL;
            n->prev=NULL;
        }
        else{
            struct PCB* temp=head;
            while(temp->next!=NULL) temp=temp->next;
            temp->next=n;
            n->next=NULL;
            n->prev=temp;
        }
    }
    struct PCB* temp=head;
    while(temp->next!=NULL) temp=temp->next;
    temp->next=head;
    head->prev=temp;
    printf("Enter the value of time quantum:");
    scanf("%d",&quant);
    struct PCB* n=head;
    while(y!=0){
        if(n->CPUBurst<=quant&&n->CPUBurst>0){
            sum+=n->CPUBurst;
            n->CPUBurst=0;
            flag=1;
        }
        else if(n->CPUBurst>quant&&n->CPUBurst>0){
            n->CPUBurst-=quant;
            sum+=quant;
        }
        if(flag==1&&n->CPUBurst==0){
            y--;
            flag=0;
            n->waitingTime=sum-(n->arrivalTime)-(n->perCBT);
            printf("ProcessID:%d   BurstTime:%d   Waitingtime:%d\n",n->procId,n->perCBT,n->waitingTime);
            wt+=n->waitingTime;
            tat+=n->waitingTime+n->perCBT;
        }
        if(n->next->arrivalTime<=sum) n=n->next;
        else n=head;
    }
    avg_wt=(wt*1.0)/NOP;
    avg_tat=(tat*1.0)/NOP;
    printf("Average Waiting Time:%f\nAverage Turn Around Time:%f",avg_wt,avg_tat);
    return 0;
}