/*
============================================================================
Name : 26.c
Author : Naman Samant
Description : Write a program to send messages to the message queue. Check $ipcs -q
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
    long msg_type;  // Message type
    char msg_text[MAX_TEXT];  // Message text
};

int main() {
    key_t key;
    int msgid;
    struct message msg;
    key = ftok("progfile", 65);  // Ensure 'progfile' exists
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    msg.msg_type = 1;
    printf("Enter message to send: ");
    fgets(msg.msg_text, MAX_TEXT, stdin);
    msg.msg_text[strcspn(msg.msg_text, "\n")] = 0;// Remove newline character
    // Send the message to the message queue
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Message sent: %s\n", msg.msg_text);
    return 0;
}

