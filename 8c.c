#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
void sigfpe_handler(int sig) {
    printf("Caught SIGFPE\n");
    _exit(0);
}
int main() {
    if (signal(SIGFPE, sigfpe_handler) == SIG_ERR) {
        perror("Error while assigning signal handler!");
        return 1;
    }
    raise(SIGFPE);
    return 0;
}
