#include "sys/socket.h"
#include "sys/types.h"
#include "stdio.h"
#include "sys/stat.h"
#include "netinet/in.h"
#include "fcntl.h"
#include "stdlib.h"
#include "arpa/inet.h"

int main() {
    int create_socket, fd, new_socket, cont;
    struct sockaddr_in address;
    char* buffer = malloc(1024);
    char fname[256];

    if((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){
        printf("Socket created\n");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15000);

    if(bind(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0){
        printf("Binding socket\n");
    }
    listen(create_socket, 3);

    int addrlen = sizeof(address);
    new_socket = accept(create_socket, (struct sockaddr *)&address, &addrlen);

    if(new_socket > 0){
        printf("Client %s connected\n", inet_ntoa(address.sin_addr));
    }
    recv(new_socket, fname, 255, 0);

    printf("Request for filename %s recieved.\n", fname);

    if((fd = open(fname, O_RDONLY)) < 0){
        perror("File open failed\n");
        return -1;
    }
    while((cont = read(fd, buffer, 1024)) > 0){
        send(new_socket, buffer, cont, 0);
    }

    printf("Request completed\n");
    close(new_socket);

    return close(create_socket);
    
}