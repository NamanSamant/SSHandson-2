/*
============================================================================
Name : 13a.c
Author : Naman Samant
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("Caught SIGINT, exiting...\n");
        exit(0); 
    } else {
        printf("Caught signal %d\n", sig);
    }
}

int main() {
    signal(SIGINT, signal_handler);
    printf("Waiting for signals (try sending SIGSTOP)...\n");
    //to keep the process alive
    while (1) {
        pause();  
    }

    return 0;
}

