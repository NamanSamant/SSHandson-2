/*
============================================================================
Name : 32b.c
Author : Naman Samant
Description : Write a program to implement semaphore to protect any critical section.
b. protect shared memory from concurrent write access
Date: 21st Sep, 2024.
============================================================================
*/
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    key_t semKey = ftok(".", 100);
    int semId = semget(semKey, 1, IPC_CREAT | 0700);
    union semun {
        int val;
    } semSet;
    semSet.val = 1;
    semctl(semId, 0, SETVAL, semSet);
    key_t shmKey = ftok(".", 200);
    int shmId = shmget(shmKey, 1024, IPC_CREAT | 0700);
    char *shmPtr = (char *)shmat(shmId, NULL, 0);
    struct sembuf semOp = {0, -1, 0}; // Lock
    semop(semId, &semOp, 1);
    printf("Writing to shared memory...\n");
    sprintf(shmPtr, "Content of shared memory");
    printf("Data in shared memory: %s\n", shmPtr);
    semOp.sem_op = 1; // Unlock
    semop(semId, &semOp, 1);
    shmdt(shmPtr);
    return 0;
}
