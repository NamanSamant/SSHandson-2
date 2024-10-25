#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

int main() {
    pid_t pid;
    printf("Enter the PID of the process to send SIGCONT: ");
    if (scanf("%d", &pid) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid PID.\n");
        return EXIT_FAILURE;
    }
    if (kill(pid, SIGCONT) == 0) {
        printf("SIGCONT signal sent to process %d.\n", pid);
    } else {
        perror("Failed to send SIGCONT");
        exit(EXIT_FAILURE);
    }
    return 0;
}s
