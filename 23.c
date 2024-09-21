/*
============================================================================
Name : 23.c
Author : Naman Samant
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    printf("Maximum number of open files: soft limit = %lu, hard limit = %lu\n", 
           rl.rlim_cur, rl.rlim_max);
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int pipe_size = fpathconf(pipefd[0], _PC_PIPE_BUF);
    if (pipe_size == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    printf("Size of a pipe (circular buffer): %d bytes\n", pipe_size);
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

