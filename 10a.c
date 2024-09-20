/*
============================================================================
Name : 10a.c
Author : Naman Samant
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sigsegv_handler(int sig) {
    printf("Caught SIGSEGV\n");
    _exit(0);
}
int main() {
    struct sigaction s;
    s.sa_handler = sigsegv_handler;
    s.sa_flags = 0;

    if (sigaction(SIGSEGV, &s, NULL) == -1) {
        perror("Error setting SIGSEGV handler");
        return 1;
    }

    raise(SIGSEGV);
    return 0;
}
