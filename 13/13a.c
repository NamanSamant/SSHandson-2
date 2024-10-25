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
/*volatile sig_atomic_t continue_received = 0;
void signal_handler(int sig){
        if (sig == SIGCONT) {
        continue_received = 1; 
    }
}*/
void signal_handler(int sig){
printf("\nSIGSTOP signal received\n");
_exit(0);
}

int main() {
    /*signal(SIGCONT, signal_handler);*/
    signal(SIGSTOP, signal_handler);
    printf("Process PID: %d\n", getpid());
    printf("Waiting for signals (try sending SIGSTOP)...\n");
    //to keep the process alive
    while (1) {
        pause();
        /*if (continue_received) {
            printf("Exiting after handling SIGCONT.\n");
            exit(0);  // Explicitly exit after handling SIGCONT
        }*/
    }
    
    return 0;
}

