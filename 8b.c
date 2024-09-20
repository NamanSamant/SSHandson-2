#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sigint_handler(int signum) {
    printf("\nSignal SIGINT has been caught!\n");
    _exit(0);
}
int main() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Error while assigning signal handler!");
        return 1;
    }
    while(1);
    return 0;
}
