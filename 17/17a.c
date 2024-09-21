/*
============================================================================
Name : 17a.c
Author : Naman Samant
Description : Write a program to execute ls -l | wc.
a. use dup
Date: 21st Sep, 2024.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>

int main() {
    int pipeEnds[2];
    pipe(pipeEnds);
    if (fork() == 0) {
        close(pipeEnds[1]); 
        close(STDIN_FILENO);
        dup(pipeEnds[0]);
        close(pipeEnds[0]);
        execlp("wc", "wc", NULL);
    } else {
        close(pipeEnds[0]); 
        close(STDOUT_FILENO);
        dup(pipeEnds[1]);
        close(pipeEnds[1]);
        execlp("ls", "ls", "-l", NULL);
    }

    return 0;
}


