#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
void setitimer_handler(int sig) {
    printf("Caught SIGVTALRM (setitimer)\n");
    _exit(0);
}
int main() {
    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error while setting the virtual timer!");
        return 1;
    }
    if (signal(SIGVTALRM, setitimer_handler) == SIG_ERR) {
        perror("Error while setting the signal handler!");
        return 1;
    }
    while (1);
    return 0;
}
