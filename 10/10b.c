/*
============================================================================
Name : 10b.c
Author : Naman Samant
Description : Write a separate program using sigaction system call to catch the following signals.
b. SIGINT
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sigint_handler(int sig) {
    printf("Caught SIGINT\n");
    _exit(0);
}
int main() {
    struct sigaction s;
    s.sa_handler = sigint_handler;
    s.sa_flags = 0;

    if (sigaction(SIGINT, &s, NULL) == -1) {
        perror("Error setting SIGINT handler");
        return 1;
    }

    while (1) {
        sleep(1);
    }

    return 0;
}
