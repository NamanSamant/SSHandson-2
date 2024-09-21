/*
============================================================================
Name : 17c.c
Author : Naman Samant
Description : Write a program to execute ls -l | wc.
c. use fcntl
Date: 21st Sep, 2024.
============================================================================
*/
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

void main() {
    int pipefileDescriptors[2];
    int pipeCurrentStatus;
    pid_t childPid;

    pipeCurrentStatus = pipe(pipefileDescriptors);

    if (pipeCurrentStatus == -1)
        perror("Error while creating the file!");
    else {
        childPid = fork();

        if (childPid == -1)
            perror("Error while forking child!");
        else if (childPid == 0) {
            close(STDIN_FILENO);
            fcntl(pipefileDescriptors[0], F_DUPFD, STDIN_FILENO);
            close(pipefileDescriptors[1]);
            execl("/usr/bin/wc", "wc", NULL);
        } else {
            close(STDOUT_FILENO);
            fcntl(pipefileDescriptors[1], F_DUPFD, STDOUT_FILENO);
            close(pipefileDescriptors[0]);
            execl("/usr/bin/ls", "ls", "-l", NULL);
        }
    }
}

