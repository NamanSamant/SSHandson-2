/*
============================================================================
Name : 8a.c
Author : Naman Samant
Description : Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sigsegv_handler(int sig)
{
    printf("Signal SIGSEGV has been caught!\n");
    _exit(0);
}
int main() {
      __sighandler_t signalStatus;

    signalStatus = signal(SIGSEGV, (void *)callback);
    if (signalStatus == SIG_ERR)
        perror("Error while assigning signal handler!");
    else
        raise(SIGSEGV);
    return 0;
}
