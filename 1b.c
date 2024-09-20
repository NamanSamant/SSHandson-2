#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigvtalrm(int signum) {
    printf("SIGVTALRM received: timer has expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, handle_sigvtalrm);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    //setting interval value as 10s and 10micros
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    // Setting the timer for ITIMER_VIRTUAL
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error setting ITIMER_VIRTUAL");
        return 1;
    }

    // Waiting for the signal
    while (1) {
        for (int i = 0; i < 100000000; i++); //This loop is added so that the program spends some time in user mode
    }

    return 0;
}

