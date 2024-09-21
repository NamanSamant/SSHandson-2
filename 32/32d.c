/*
============================================================================
Name : 32d.c
Author : Naman Samant
Description : Write a program to implement semaphore to protect any critical section.
d. remove the created semaphore
Date: 21st Sep, 2024.
============================================================================
*/
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
int main() {
    key_t semKey = ftok(".", 400);
    int semId = semget(semKey, 1, IPC_CREAT | 0700);
    printf("Press enter to delete the semaphore...\n");
    getchar();
    semctl(semId, 0, IPC_RMID);
    printf("Semaphore deleted.\n");
    return 0;
}
