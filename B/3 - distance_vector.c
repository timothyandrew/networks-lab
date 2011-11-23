#include "stdio.h"
#define size 5

typedef struct {
  int best_outgoing[size];
  int hop_count[size];
} router;

void build_initial_hops(int adj[][size], router* routers){
  int i,j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      if(adj[i][j] == 1){
        routers[i].hop_count[j] = 1;
      } else if(i==j){
        routers[i].hop_count[j] = 0;
      } else {
        routers[i].hop_count[j] = 99;
      }
    }
  }
}

void build_hop_count(router* routers){
  int i,j,k;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      for(k=0;k<size;k++){
        if(i!=j && j!=k){
          if(routers[i].hop_count[j] == 1 && routers[j].hop_count[k] < routers[i].hop_count[k]){
            routers[i].hop_count[k] = routers[j].hop_count[k] + 1;
          }
        }
      }
    }
  }
}

void build_outgoing_line(router* routers){
  int i,j,k;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      if(i!=j && routers[i].hop_count[j] == 1){
        routers[i].best_outgoing[j] = j;
      } else if(i!=j){
        int smallest = 99;
        int best;
        for(k=0;k<size;k++){
          if(j!=k && routers[i].hop_count[k] == 1){
            int tmp = routers[k].hop_count[j];
            if(tmp<=smallest){
              smallest = tmp;
              best = k;
            }
          }
        }
        routers[i].best_outgoing[j] = best;
      }
    } 
  }
}

void print(router* routers){
  int i,j;
  char idx[size] = {'A', 'B', 'C', 'D', 'E'};
  for(i=0;i<size;i++){
    printf("=======Router #%d=========\n", i+1);
    for(j=0;j<size;j++){
      int outgoing = routers[i].best_outgoing[j];
      if(i==j){ outgoing = j; }
      printf("To #%d, Best route: %c, No of hops: %d\n", j+1, outgoing < size ? idx[outgoing] : outgoing, routers[i].hop_count[j]);
    }
    printf("\n\n");
    //printf("==========================\n");
  }
}

int main(int argc, char* argv[]){
  int adj[size][size] = {
    {99,1,1,99,99},
    {1,99,99,99,99},
    {1,99,99,1,1},
    {99,99,1,99,99},
    {99,99,1,99,99},
  };

  router routers[size];

  build_initial_hops(adj, routers);
  int i;

  for(i=0; i<size; i++){
    build_hop_count(routers);
    build_outgoing_line(routers);
  }

  print(routers);
}