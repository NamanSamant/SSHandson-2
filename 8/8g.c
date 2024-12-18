/*
============================================================================
Name : 8g.c
Author : Naman Samant
Description : Write a separate program using signal system call to catch the following signals.
g. SIGPROF (use setitimer system call)
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
void setitimer_handler(int sig) {
    printf("Caught SIGPROF (setitimer)\n");
    _exit(0);
}
int main() {
    struct sigaction sa;
    struct itimerval itv;
    itv.it_interval.tv_sec = 5;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 0;
    setitimer(ITIMER_PROF, &itv, NULL);
    sa.sa_handler = setitimer_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGPROF, &sa, NULL);
    while (1) {
        for (int i = 0; i < 1000; i++);
    }
    return 0;
}
