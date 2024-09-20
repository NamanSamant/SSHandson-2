#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
void handle_sigalrm(int signum) {
    printf("SIGALRM received: timer has expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, handle_sigalrm);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    //here we are setting the interval value as 10 seconds and 10 microseconds
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    //Here we are setting the timer for ITIMER_REAL
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error setting ITIMER_REAL");
        return 1;
    }
    // Waiting for the signal
    while (1) {
        pause();
    }

    return 0;
}

