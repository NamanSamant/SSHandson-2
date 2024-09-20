#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
void setitimer_handler(int sig) {
    printf("Caught SIGPROF (setitimer)\n");
}
int main() {
    struct sigaction sa;
    struct itimerval itv;
    itv.it_interval.tv_sec = 5;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 5;
    itv.it_value.tv_usec = 0;
    setitimer(ITIMER_PROF, &itv, NULL);
    sa.sa_handler = setitimer_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGPROF, &sa, NULL);
    while (1) {
        pause();
    }
    return 0;
}
