/*
============================================================================
Name : 15.c
Author : Naman Samant
Description : Write a simple program to send some data from parent to the child process.
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main() {
    int pipefds[2];
    pid_t pid;
    char write_msg[] = "hello world";
    char read_msg[100];
    if (pipe(pipefds) == -1) {
        perror("Pipe failed");
        return 1;
    }
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    if (pid > 0) {
        close(pipefds[0]);  
        printf("Parent: Sending data to child: %s\n", write_msg);
        write(pipefds[1], write_msg, strlen(write_msg) + 1);  
        close(pipefds[1]);  
    } else {  
        close(pipefds[1]);
        read(pipefds[0], read_msg, sizeof(read_msg));
        printf("Child: Received data from parent: %s\n", read_msg);
        close(pipefds[0]);  
    }

    return 0;
}

