/*
============================================================================
Name : 20a.c
Author : Naman Samant
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
    const char *fifoPath = "my_fifo";
    char message[] = "Hello this is a message from 20a!";
    int fd = open(fifoPath, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open FIFO for writing");
        return 1;
    }
    write(fd, message, sizeof(message));
    close(fd);
    return 0;
}

