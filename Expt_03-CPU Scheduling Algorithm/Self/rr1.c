#include <stdio.h>
#include <stdlib.h>

typedef struct PCB{
  int pid;
  int cycleBursts;
  int wait;
  int arrivalTime;
  struct PCB* next;
}PCB;
PCB* head = NULL;

void insert(PCB* temp){
  if (head == NULL){
    head = temp;
    head->next = head;
  }
  else{
    PCB* temp1 = head;
    while(temp1->next!=head && temp1->next->arrivalTime<=temp->arrivalTime){
      temp1 = temp1->next;
    }
    temp->next = temp1->next;
    temp1->next=temp;
  }
}

void del(PCB* temp){
  PCB* temp1 = head;
  while(temp1->next!=temp){
    temp1 = temp1->next;
  }
  temp1->next = temp->next;
  if(head == temp){
    head = temp->next;
    temp1->next = head;
  }
}

void print(){
  PCB* temp1 = head;
  printf("pid\tcycleburst\tarrival\n");
  do{
    printf("%d\t\t%d\t\t%d\n", temp1->pid, temp1->cycleBursts, temp1->arrivalTime);
    temp1 = temp1->next;
  }while(temp1!=head);
  printf("\n");
}


int main(){
  int n;
  float total_wait = 0.0;
  int clock = 0;
  int quantum;
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  for(int i = 0; i<n; i++){
    PCB* temp = (PCB*)malloc(sizeof(PCB));
    printf("Enter the cycleburst and arrival time: ");
    scanf("%d", &temp->cycleBursts);
    scanf("%d", &temp->arrivalTime);
    temp->pid = i+1;
    insert(temp);
  }
  print();
  printf("Enter the quantum time slice: ");
  scanf("%d", &quantum);
  while(head!=NULL && !(head->arrivalTime<0) && head->cycleBursts>0){
    print();
    PCB* temp1 = head;
    do{
      if(temp1->cycleBursts>=0 && temp1->arrivalTime<=clock){
        break;
      }
      temp1 = temp1->next;
    }while(temp1!=head);    
    if(temp1->cycleBursts <= quantum){
      temp1->wait+=clock-temp1->arrivalTime;
      clock+=temp1->cycleBursts;
      temp1->cycleBursts = 0;
      total_wait += temp1->wait;
      del(temp1);
      printf("P%d(wait: %d)", temp1->pid, temp1->wait);
      //free(temp1);
    }
    else if(temp1->cycleBursts > quantum){
      del(temp1);
      temp1->wait+=clock-temp1->arrivalTime;
      temp1->arrivalTime = clock+quantum;
      temp1->cycleBursts-=quantum;
      clock+=quantum;
      insert(temp1);
    }
    else{
      clock++;
    }
  }
    printf("\n\nAverage waiting time: %lf", total_wait/(double)(n));
    printf("\nAverage turn around time: %lf", (total_wait + (double)(clock))/(double)(n));
  return 0;
}