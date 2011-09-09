#include "stdio.h"
#include "stdlib.h"

#define bsize 500
#define osize 50
#define input 5

#define RAND_MAX 300

int bucket = 0;

int main(){
  int i,ip, free_space;
  
  srand(50);
  
  for(i=0; i<input; i++){
    ip = rand() % RAND_MAX;
    free_space = bsize - bucket;
    printf("-------------------------------------------\nInput #%d - Bucket filled up to = %d   Input = %d\n------------------------------------------\n", i+1, bucket, ip);
  
    
    if(ip > free_space + osize){
      printf("Input greater than available bucket space + output size. Transmitted %d\nDiscarding %d.\nAdded %d to bucket.\n", osize, ip - osize - (free_space), free_space + osize);
      bucket = bsize;
    } else if(ip + bucket < osize){
      bucket += ip;
      printf("Not enough data to transmit. Bucket contents smaller than output size.\nAdded %d to bucket.\nTransmitted 0\n", ip);
    } else if(ip + bucket >= osize){
      bucket += ip;
      printf("Transmitted %d\nAdded %d to bucket\n", osize, ip-osize);
      bucket -= osize;      
    }
    
    //printf("Remaining bucket space is %d.\n", bucket);
  }
}
