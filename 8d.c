#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
void sigalrm_handler(int sig) {
    printf("Caught SIGALRM (alarm)\n");
    _exit(0);
}
int main() {
    alarm(3);
    if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
        perror("Error setting signal handler!");
        return 1;
    }
    while (1);
    return 0;
}
