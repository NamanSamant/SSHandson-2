/*
============================================================================
Name : 16.c
Author : Naman Samant
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe1[2], pipe2[2];  
    pid_t pid;
    char parent_msg[] = "Hello this data is from parent!";
    char child_msg[] = "Hello this data is from child!";
    char read_buffer[100];
    if (pipe(pipe1) == -1) {
        perror("Pipe1 failed");
        return 1;
    }
    if (pipe(pipe2) == -1) {
        perror("Pipe2 failed");
        return 1;
    }
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    if (pid > 0) {  
        close(pipe1[0]);  
        close(pipe2[1]);  
        printf("Parent: Sending to child: %s\n", parent_msg);
        write(pipe1[1], parent_msg, strlen(parent_msg) + 1);  
        close(pipe1[1]); 
        read(pipe2[0], read_buffer, sizeof(read_buffer));
        printf("Parent: Received from child: %s\n", read_buffer);
        close(pipe2[0]);
    } else {  
        close(pipe1[1]);  
        close(pipe2[0]);  
        read(pipe1[0], read_buffer, sizeof(read_buffer));
        printf("Child: Received from parent: %s\n", read_buffer);
        close(pipe1[0]);
        printf("Child: Sending to parent: %s\n", child_msg);
        write(pipe2[1], child_msg, strlen(child_msg) + 1);
        close(pipe2[1]);  
    }

    return 0;
}

