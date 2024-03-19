#include <stdio.h>
#include <stdlib.h>

typedef struct PCB{
  int procId;
  int waitingTime;
  int arrivalTime;
  int cpuBurst;
  int priority;
  int tat;
  struct PCB* next;
  struct PCB* prev;
}PCB;

PCB* head = NULL;

void insert(PCB* temp){
  if(head == NULL){
    head = temp;
  }
  else{
    if(head->priority > temp->priority){
      temp->next = head;
      head->prev = temp;
      head = temp;
    }
    else{
      PCB* temp1 = head;
      while(temp1->next !=NULL && temp1->next->priority < temp->priority){
        temp1 = temp1->next;
      }
  
      temp->next = temp1->next;
      if(temp1->next!=NULL){
        temp1->next->prev = temp;
      }
      temp1->next = temp;
      temp->prev = temp1;
    }
  }
}

void deleteProcess(PCB* temp){
  if(head == temp){
    head = head->next;
  }
  else{
    temp->prev->next = temp->next;
  }
  if(temp->next!=NULL){
    temp->next->prev = temp->prev;
  }
}

void print(){
  PCB* temp1 = head;
  printf("PID\tPriority\tCPU Burst\tArrival Time\n");
  while(temp1!=NULL){
    printf("%d\t\t%d\t\t%d\t\t%d\n", temp1->procId, temp1->priority, temp1->cpuBurst, temp1->arrivalTime);
    temp1 = temp1->next;
  }
  printf("-----------------------------------------\n");
}

int main(){
  int n;
  PCB* temp1;
  int clock = 0;
  float total_waiting = 0.0;
  float turnaround = 0.0;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  for(int i = 0; i<n; i++){
    PCB* temp = (PCB*)malloc(sizeof(PCB));
    printf("Enter the priority, arrival time and cycle bursts for p%d: ", i+1);
    scanf("%d", &temp->priority);
    scanf("%d", &temp->arrivalTime);
    scanf("%d", &temp->cpuBurst);
    temp->procId = i+1;
    temp -> waitingTime = 0;
    temp->tat = temp->cpuBurst;
    insert(temp);
  }

  //print();
  while(head!=NULL){
    temp1 = head;
    while(temp1!=NULL){
      print();
      if(temp1->arrivalTime<=clock && temp1->cpuBurst!=0){
        break;
      }
      temp1 = temp1->next;
    }
    if(temp1!=NULL){
      deleteProcess(temp1);
      temp1->cpuBurst--;
      if(temp1->cpuBurst==0){
        printf("P%d(wait: %d)->", temp1->procId, temp1->waitingTime);
        total_waiting+=temp1->waitingTime;
        turnaround += (temp1->waitingTime+temp1->tat);
        free(temp1);
      }
      else{
        temp1->waitingTime += clock - temp1->arrivalTime;
        temp1->arrivalTime = clock+1;
        insert(temp1);
      }
    }
    clock++;
  }
  printf("END\n");
  printf("Average waiting time: %f\n", total_waiting/n);
  printf("average turnaround time: %f\n", turnaround/n);

  return 0;
}