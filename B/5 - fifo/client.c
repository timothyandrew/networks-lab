#include "stdio.h"
#include "string.h"
#include "fcntl.h"

int main() {
    char fname[256];
    ssize_t cont;
    char buffer[512];

    int writefd = open("fifo1", O_WRONLY, 0);
    int readfd = open("fifo2", O_RDONLY, 0);

    printf("Enter filename: "); scanf("%s", fname);

    write(writefd, fname, strlen(fname));
    
    while((cont=read(readfd, buffer, 512)) > 0){
        printf("%s", buffer);
    }

    close(readfd);
    close(writefd);

    return 0;
}