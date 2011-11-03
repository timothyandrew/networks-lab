#include "stdio.h"
#include "fcntl.h"

int main() {
    char fname[256];
    ssize_t cont;
    int fd;
    char buffer[512];

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    int readfd = open("fifo1", O_RDONLY, 0);
    int writefd = open("fifo2", O_WRONLY, 0);

    read(readfd, fname, 255);   

    if((fd = open(fname, O_RDWR)) < 0){
        perror("File doesn't exist.");
        return -1;
    } else {
        while((cont = read(fd, buffer, 512)) > 0){
            write(writefd, buffer, cont);
        }
    }

    close(readfd);   unlink("fifo1");
    close(writefd);  unlink("fifo2");
}