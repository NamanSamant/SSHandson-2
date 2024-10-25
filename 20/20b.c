/*
============================================================================
Name : 20b.c
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
    const char *fifoPath = "./myfifo";
    char buffer[100];
    int fd = open(fifoPath, O_RDONLY);
    if (fd == -1) {
        perror("Unable to open FIFO for reading");
        return 1;
    }
    int bytesRead = read(fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    close(fd);
    return 0;
}

