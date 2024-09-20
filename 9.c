/*
============================================================================
Name : 9.c
Author : Naman Samant
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
Date: 20th Sep, 2024.
============================================================================
*/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_reset(int signalId) {
    printf("\nHere SIGINT is getting reset to its default action\n");
    signal(SIGINT, SIG_DFL);
}

int main() {
    signal(SIGINT, SIG_IGN);
    printf("Ignored SIGINT\n");
    sleep(2);
    signal(SIGINT, handle_reset);
    printf("\nSIGINT reset, press Ctrl + C\n");
    while (1) {
        sleep(1);
    }

    return 0;
}
