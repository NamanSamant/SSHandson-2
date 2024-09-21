/*
============================================================================
Name : 25.c
Author : Naman Samant
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds msg_info;
    key = ftok(".", 65);
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
    printf("Access Permissions: %o\n", msg_info.msg_perm.mode);
    printf("Owner UID: %u\n", msg_info.msg_perm.uid);
    printf("Owner GID: %u\n", msg_info.msg_perm.gid);
    printf("Time of Last Message Sent: %s", ctime(&msg_info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&msg_info.msg_rtime));
    printf("Time of Last Change: %s", ctime(&msg_info.msg_ctime));
    printf("Current Size of Queue (bytes): %lu\n", msg_info.__msg_cbytes);
    printf("Number of Messages in Queue: %lu\n", msg_info.msg_qnum);
    printf("Maximum Number of Bytes Allowed in Queue: %lu\n", msg_info.msg_qbytes);
    printf("PID of Last msgsnd: %u\n", msg_info.msg_lspid);
    printf("PID of Last msgrcv: %u\n", msg_info.msg_lrpid);
    return 0;
}

