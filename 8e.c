#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
void setitimer_handler(int sig) {
    printf("Caught SIGALRM (setitimer)\n");
    _exit(0);
}
int main() {
    struct itimerval timer;
    signal(SIGALRM, setitimer_handler);
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    while(1);
    return 0;
}
