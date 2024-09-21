/*
============================================================================
Name : 24.c
Author : Naman Samant
Description : Write a program to create a message queue and print the key and message queue id.
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
    key = ftok(".", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);
    return 0;
}

