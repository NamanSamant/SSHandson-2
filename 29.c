/*
============================================================================
Name : 29.c
Author : Naman Samant
Description : Write a program to remove the message queue.
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
int main() {
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Message queue removed successfully.\n");
    return 0;
}

