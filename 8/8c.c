/*
============================================================================
Name : 8c.c
Author : Naman Samant
Description : Write a separate program using signal system call to catch the following signals.
c. SIGFPE
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
void sigfpe_handler(int sig) {
    printf("Caught SIGFPE\n");
    _exit(0);
}
int main() {
    if (signal(SIGFPE, sigfpe_handler) == SIG_ERR) {
        perror("Error while assigning signal handler!");
        return 1;
    }
    raise(SIGFPE);
    return 0;
}
