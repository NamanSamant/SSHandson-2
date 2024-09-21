/*
============================================================================
Name : 32c.c
Author : Naman Samant
Description : Write a program to implement semaphore to protect any critical section.
c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 21st Sep, 2024.
============================================================================
*/
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    key_t semKey = ftok(".", 300);
    int semId = semget(semKey, 1, IPC_CREAT | 0700);
    union semun {
        int val;
    } semSet;
    semSet.val = 2; // Counting semaphore
    semctl(semId, 0, SETVAL, semSet);
    struct sembuf semOp = {0, -1, 0}; // Lock for resource access
    semop(semId, &semOp, 1);
    printf("Accessing resource 1\n");
    sleep(1);
    semOp.sem_op = 1; // Unlock for resource access
    semop(semId, &semOp, 1);
    return 0;
}
