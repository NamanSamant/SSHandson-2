/*
============================================================================
Name : 21b.c
Author : Naman Samant
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 21st Sep, 2024.
============================================================================
*/
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
char *pipeA = "./pipeA";
char *pipeB = "./pipeB";
void setup_pipes() {
    if (mkfifo(pipeA, 0666) == -1 && errno != EEXIST) {
        perror("Error creating pipeA");
    }
    if (mkfifo(pipeB, 0666) == -1 && errno != EEXIST) {
        perror("Error creating pipeB");
    }
}
int main() {
    int writeFd, readFd;
    char buffer[100];
    setup_pipes();
    readFd = open(pipeA, O_RDONLY);
    writeFd = open(pipeB, O_WRONLY);
    if (writeFd == -1 || readFd == -1) {
        perror("Error opening pipes");
        return 1;
    }
    read(readFd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    write(writeFd, "Message from B to A", 19);
    close(readFd);
    close(writeFd);
    return 0;
}
