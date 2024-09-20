/*
============================================================================
Name : 10c.c
Author : Naman Samant
Description : Write a separate program using sigaction system call to catch the following signals.
c. SIGFPE
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sigfpe_handler(int sig) {
    printf("Caught SIGFPE\n");
    _exit(0);
}
int main() {
    struct sigaction sigfpeAction;
    sigfpeAction.sa_handler = sigfpe_handler;
    sigfpeAction.sa_flags = 0;

    if (sigaction(SIGFPE, &sigfpeAction, NULL) == -1) {
        perror("Error setting SIGFPE handler");
        return 1;
    }

    raise(SIGFPE);

    return 0;
}
