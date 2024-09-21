/*
============================================================================
Name : 18.c
Author : Naman Samant
Description : Write a program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc ? Use only dup2.
Date: 21st Sep, 2024.
============================================================================
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
int main() {
    int pipeLsToGrep[2], pipeGrepToWc[2];
    pipe(pipeLsToGrep);
    pipe(pipeGrepToWc);
    if (fork() == 0) {
        close(pipeLsToGrep[0]);
        close(pipeLsToGrep[1]);
        close(pipeGrepToWc[1]);
        dup2(pipeGrepToWc[0], STDIN_FILENO);
        close(pipeGrepToWc[0]);
        execlp("wc", "wc", NULL);
        return 1;
    }
    if (fork() == 0) {
        close(pipeLsToGrep[1]);
        dup2(pipeLsToGrep[0], STDIN_FILENO);
        close(pipeLsToGrep[0]);

        close(pipeGrepToWc[0]);
        dup2(pipeGrepToWc[1], STDOUT_FILENO);
        close(pipeGrepToWc[1]);

        execlp("grep", "grep", "^d", NULL);
        return 1;
    }
    close(pipeLsToGrep[0]);
    dup2(pipeLsToGrep[1], STDOUT_FILENO);
    close(pipeLsToGrep[1]);
    close(pipeGrepToWc[0]);
    close(pipeGrepToWc[1]);
    execlp("ls", "ls", "-l", NULL);
    return 1;
}
