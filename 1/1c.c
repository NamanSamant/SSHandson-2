/*
============================================================================
Name : 1c.c
Author : Naman Samant
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
c. ITIMER_PROF
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigprof(int signum) {
    printf("SIGPROF received: ITIMER_PROF timer expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGPROF, handle_sigprof);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    //Setting the interval value as 10 seconds and 10 microseconds
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    // Setting the timer for ITIMER_PROF
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("Error setting ITIMER_PROF");
        return 1;
    }

    // Waiting for the signal
    while (1) {
        for(int i=0;i<10000000;i++);
    }

    return 0;
}

