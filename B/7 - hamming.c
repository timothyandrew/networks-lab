#include "stdio.h"
#include "stdlib.h"

void print(int arr[], int length){
  int i;
  for(i=0;i<length;i++){
    printf("%d\n", arr[i]);
  }
}

int* encode(int data[4], int G[4][7]){
  int i,j;
  int* result = malloc(7*sizeof(int));
  for(i=0;i<7;i++){
    result[i] = 0;
    for(j=0;j<4;j++){
      result[i] += (data[j] * G[j][i]);
    }
    result[i] %= 2;
  }
  return result;
}

int* decode(int code[7], int H[3][7]){
  int i,j;
  int* result = malloc(3*sizeof(int));
  for(i=0;i<3;i++){
    result[i] = 0;
    for(j=0;j<7;j++){
      result[i] += (code[j] * H[i][j]);
    }
    result[i] %= 2;
  }
  return result;  
}

void transmit(int code[7]){
  code[5] = code[0] == 1 ? 0 : 1;
}

void find_error(int decoded[3], int H[3][7]){
  int i;
  for(i=0;i<3;i++){
    if(decoded[i]==1){
      int x,y,z;
      for(x=0;x<7;x++){
        int flag = 1;
        for(y=0;y<3;y++){
          if(decoded[y] == H[y][x]){
            flag = flag == 0 ? 0 : 1;
          } else {
            flag = 0;   
          }
        }
        if(flag == 1){
          printf("Error detected at bit %d\n", x+1);
          return;
        }
      }
      return;
    }
  }
  printf("No error!\n");
}

int main(int argc, char* argv[]){
  int G[4][7] = {
    {0,1,1,1,0,0,0},
    {1,0,1,0,1,0,0},
    {1,1,0,0,0,1,0},
    {1,1,1,0,0,0,1}
  };
  
  int H[3][7] = {
    {1,0,0,0,1,1,1},
    {0,1,0,1,0,1,1},
    {0,0,1,1,1,0,0}
  }; 
  
  int data[4] = {1,0,1,0}; 
  int* code = encode(data, G);
  transmit(code);
  int* decoded = decode(code, H);
  find_error(decoded, H);
}