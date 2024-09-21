/*
============================================================================
Name : 8b.c
Author : Naman Samant
Description : Write a separate program using signal system call to catch the following signals.
b. SIGINT
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sigint_handler(int signum) {
    printf("\nSignal SIGINT has been caught!\n");
    _exit(0);
}
int main() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Error while assigning signal handler!");
        return 1;
    }
    while(1);
    return 0;
}
