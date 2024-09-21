/*
============================================================================
Name : 28.c
Author : Naman Samant
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
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
    struct msqid_ds msg_info;
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
    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Current Permissions: %o\n", msg_info.msg_perm.mode);
    msg_info.msg_perm.mode = 0664;
    if (msgctl(msgid, IPC_SET, &msg_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Updated Permissions: %o\n", msg_info.msg_perm.mode);
    return 0;
}

