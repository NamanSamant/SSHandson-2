/*
============================================================================
Name : 8d.c
Author : Naman Samant
Description : Write a separate program using signal system call to catch the following signals.
d. SIGALRM (use alarm system call)
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
void sigalrm_handler(int sig) {
    printf("Caught SIGALRM (alarm)\n");
    _exit(0);
}
int main() {
    alarm(3);
    if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
        perror("Error setting signal handler!");
        return 1;
    }
    while (1);
    return 0;
}
