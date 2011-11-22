#include "stdio.h"
#include "string.h"
#define size 3

typedef struct {
  int seqNo;
  char data[size+1];
} packet;

void make_packets(char* msg, packet* packets){
  int i,j;

  int count = 0;
  for(i=0; i<strlen(msg);i += 3){
    packets[count].seqNo = count;
    for(j=0;j<3;j++){
      packets[count].data[j] = msg[i+j];
    }
    count++;
  }
}

void print(packet* packets, int length){
  int i;
  printf("Sequence is: ");
  for(i=0; i<length; i++){
    printf("%d ", packets[i].seqNo);
  }

  printf("\nData is: ");
  for(i=0; i<length; i++){
    printf("%s", packets[i].data);
  }
  printf("\n\n");
}

void shuffle(packet* packets, int length){
  int i;
  for(i=0; i<length; i++){
    int x = rand() % length;
    int y = rand() % length;

    packet tmp = packets[x];
    packets[x] = packets[y];
    packets[y] = tmp;
  }
}

void unshuffle(packet* packets, int length){
  int i,j;
  
  for(i=0;i<length;i++){
    for(j=0;j<length;j++){
      if(packets[j].seqNo == i){
        packet tmp = packets[i];
        packets[i] = packets[j];
        packets[j] = tmp;
      }
    }
  }
}

int main(int argc, char* argv[]){
  char* msg = "Hello, my name is timothy.";
  int num_of_packets = (strlen(msg)/size)+1;
  packet packets[num_of_packets];

  make_packets(msg, packets);
  shuffle(packets, num_of_packets);
  print(packets, num_of_packets);

  unshuffle(packets, num_of_packets);
  print(packets, num_of_packets);
}