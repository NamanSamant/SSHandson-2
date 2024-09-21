/*
============================================================================
Name : 11.c
Author : Naman Samant
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void ignore_sigint(int sig) {
    printf("SIGINT received but ignored.\n");
}

int main() {
    struct sigaction sa_ignore, sa_default;

    sa_ignore.sa_handler = ignore_sigint;
    sigemptyset(&sa_ignore.sa_mask);  
    sa_ignore.sa_flags = 0;

    if (sigaction(SIGINT, &sa_ignore, NULL) == -1) {
        perror("Error setting signal handler for SIGINT");
        exit(EXIT_FAILURE);
    }

    printf("SIGINT is ignored for 5 seconds. Press Ctrl+C during this time.\n");
    sleep(5);
    sa_default.sa_handler = SIG_DFL;
    sigemptyset(&sa_default.sa_mask); 
    sa_default.sa_flags = 0;

    if (sigaction(SIGINT, &sa_default, NULL) == -1) {
        perror("Error resetting signal handler for SIGINT");
        exit(EXIT_FAILURE);
    }

    printf("SIGINT is now reset to default. Press Ctrl+C to terminate the program.\n");
    while (1) {
        printf("Running... Press Ctrl+C to exit.\n");
        sleep(2);
    }

    return 0;
}

