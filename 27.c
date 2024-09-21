/*
============================================================================
Name : 27.c
Author : Naman Samant
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define MAX_TEXT 100
struct message {
    long msg_type;  
    char msg_text[MAX_TEXT];  
};
void receive_message(int msgid, int flag) {
    struct message msg;
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 0, flag) == -1) {
        if (errno == ENOMSG) {
            printf("No messages available in the queue.\n");
        } else {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Received message: %s\n", msg.msg_text);
    }
}
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
    printf("Receiving messages with flag 0:\n");
    receive_message(msgid, 0); 
    printf("Receiving messages with IPC_NOWAIT flag:\n");
    receive_message(msgid, IPC_NOWAIT); 
    return 0;
}

