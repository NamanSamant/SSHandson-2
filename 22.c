/*
============================================================================
Name : 22.c
Author : Naman Samant
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 21st Sep, 2024.
============================================================================
*/
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
char *fifoPath = "./myfifo1";
void setup_fifo() {
    if (mkfifo(fifoPath, 0666) == -1 && errno != EEXIST) {
        perror("Error creating FIFO");
    }
}
int main() {
    int fifoFd, result;
    fd_set readFds;
    struct timeval timeout;
    char buffer[100];
    setup_fifo();
    fifoFd = open(fifoPath, O_RDONLY | O_NONBLOCK);
    if (fifoFd == -1) {
        perror("Error opening FIFO");
        return 1;
    }
    FD_ZERO(&readFds);
    FD_SET(fifoFd, &readFds);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    printf("Waiting for data to be written into the FIFO (10-second timeout)...\n");
    result = select(fifoFd + 1, &readFds, NULL, NULL, &timeout);
    if (result == -1) {
        perror("Error during select");
        close(fifoFd);
        return 1;
    } else if (result == 0) {
        printf("Timeout occurred! No data was written to the FIFO within 10 seconds.\n");
    } else {
        if (FD_ISSET(fifoFd, &readFds)) {
            int bytesRead = read(fifoFd, buffer, sizeof(buffer) - 1);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
                printf("Data received: %s\n", buffer);
            } else {
                perror("Error reading from FIFO");
            }
        }
    }
    close(fifoFd);
    return 0;
}
