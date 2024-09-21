/*
============================================================================
Name : 17b.c
Author : Naman Samant
Description : Write a program to execute ls -l | wc.
b. use dup2
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main() {
    int pipeEnds[2];
    pipe(pipeEnds);

    if (fork() == 0) {
        close(pipeEnds[1]); 
        dup2(pipeEnds[0], STDIN_FILENO); 
        close(pipeEnds[0]);
        execlp("wc", "wc", NULL);
    } else {
        close(pipeEnds[0]); 
        dup2(pipeEnds[1], STDOUT_FILENO); 
        close(pipeEnds[1]);
        execlp("ls", "ls", "-l", NULL);
    }

    return 0;
}

