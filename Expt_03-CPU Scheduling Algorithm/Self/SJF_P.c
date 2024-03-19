#include <stdio.h>
#include <stdlib.h>

//creating the struct
typedef struct PCB{
    int procId;
    int cpuBurst;
    int waitingTime;
    int arrivalTime;
    struct PCB* next;
    struct PCB* prev;
}PCB;

PCB* head = NULL;

// inserts the nodes in the order of the cycle bursts
void addProcess(PCB* temp){
  PCB* temp1;
  
  if(head == NULL){
    head = temp;
  }

  else{
    // in case of the beginning of the list
    if(head->cpuBurst > temp->cpuBurst){
      head->prev = temp;
      temp->next = head;
      head = temp;
    }
    // in case of middle of the list
    else{
      temp1 = head;
      while(temp1->next!=NULL && temp1->next->cpuBurst<temp->cpuBurst){
        //check for the->next node as we have to addProcess before it
        temp1 = temp1->next;
      }

      temp->next = temp1->next;
      if(temp1->next != NULL){
        // in case of adding at the end
        temp1->next->prev = temp;
      }
      temp->prev = temp1;
      temp1->next = temp;
    }
  }
}

void deleteProcess(PCB* temp){
  //printf("received %d node", temp->procId);
  if (temp == head)
    // in case we are removing the head there is no previous node
    head = head->next;
  else
    temp->prev->next = temp->next;
  if(temp->next!=NULL)
    // in case we are removing the last element, there is no next element
    temp->next->prev = temp->prev;
}

void print(){
  // print the current status
  PCB* temp1 = head;
  printf("pid\tcycle_burst\tarrival_time\n");
  while(temp1!=NULL){
    printf("%d\t\t%d\t\t%d\n", temp1->procId, temp1->cpuBurst, temp1->arrivalTime);
    temp1 = temp1->next;
  }
}


int main(){
  int n;
  float total_wait = 0.0;
  PCB* temp1;
  int clock = 0;
  printf("Enter the number of processes: ");
  scanf("%d",&n);

  for(int i = 0; i<n; i++){
    PCB* temp = (PCB*)malloc(sizeof(PCB));
    printf("Enter the arrival time and the cycle burst: ");
    scanf("%d", &temp->arrivalTime);
    scanf("%d", &temp->cpuBurst);
    temp->procId = i+1;
    addProcess(temp); //inserting the new node
  }
  temp1 = head;
  while(head!=NULL){ // stops when there are no elements remaining
    temp1 = head;
    while(temp1!=NULL){
      if(temp1->arrivalTime <= clock && temp1->cpuBurst>0){
        //checking for the process with teh shortest running and has arrived
        //printf("exiting the sub loop with p%d at %d time\n", temp1->procId, clock);
        break;
      }
      else{
        temp1 = temp1->next;
      }
    }
    if(temp1!=NULL){
      // checking if any process has arrived or not using teh above condition, else will result NULL(beyond the last element)
      
      //printf("inside the main thing with %d process\n", temp1->procId);
      deleteProcess(temp1); //remove the node
      temp1->cpuBurst--; 
      if(temp1->cpuBurst == 0){
        //in case the cycles are done
        printf("P%d(waitingTime: %d)->", temp1->procId, temp1->waitingTime);
        total_wait+=temp1->waitingTime;
        free(temp1);
      }
      else{
        //printf("reducing...\n");
        //printf("arrival time: %d, clock: %d for p%d\n", temp1->arrivalTime, clock, temp1->procId);

        //else addProcess the element again
          temp1->waitingTime += clock-temp1->arrivalTime; //update the waiting time
          temp1->arrivalTime = clock+1; //update to new arrival time, +1 is done so that, if the same process runs for 2 or more cycles, it doesnt add up the waiting time in teh next loop
          addProcess(temp1);
      }
      //print();
    }
    clock++; //increment clock for each cycle
  }
  printf("END\n");
  printf("Average waiting time: %f", total_wait/n);
  
  return 0;
}