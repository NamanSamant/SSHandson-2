/*
============================================================================
Name : 14.c
Author : Naman Samant
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefds[2];
    pid_t pid;
    char write_msg[] = "Hello how are you";
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
        printf("Parent: Writing to the pipe: %s\n", write_msg);
        write(pipefds[1], write_msg, strlen(write_msg) + 1);
        close(pipefds[1]);  
    } else {  
        close(pipefds[1]);  
        read(pipefds[0], read_msg, sizeof(read_msg));
        printf("Child: Read from the pipe: %s\n", read_msg);
        close(pipefds[0]); 
    }
    return 0;
}

