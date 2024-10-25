/*
============================================================================
Name : 12.c
Author : Naman Samant
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        printf("Child: My PID is %d. My Parent's PID is %d\n", getpid(), getppid());
        printf("Child: Sending SIGKILL signal to Parent (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL);
        sleep(3);
        
        printf("Child: After killing parent, my new Parent's PID is %d\n", getppid());
        printf("Child: I am now an orphan and adopted by init/systemd.\n");
        sleep(3);
    }
    else{
        printf("Parent: My PID is %d. My Child's PID is %d\n", getpid(), pid);
        sleep(10); 
    }
    return 0;
}



