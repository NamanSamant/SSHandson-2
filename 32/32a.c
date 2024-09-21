/*
============================================================================
Name : 32a.c
Author : Naman Samant
Description : Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
Date: 21st Sep, 2024.
============================================================================
*/
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main() {
    int fileDescriptor, data;
    key_t semKey = ftok(".", 500);
    int semId = semget(semKey, 1, IPC_CREAT | 0700);
    union semun {
        int val;
    } semSet;
    semSet.val = 1;
    semctl(semId, 0, SETVAL, semSet);
    
    struct sembuf semOp = {0, -1, 0};//locking
    semop(semId, &semOp, 1);

    fileDescriptor = open("./ticket.txt", O_CREAT | O_RDWR, 0700);
    read(fileDescriptor, &data, sizeof(data));
    data = (data == 0) ? 1 : data + 1; 
    lseek(fileDescriptor, 0, SEEK_SET);
    write(fileDescriptor, &data, sizeof(data));
    printf("Your ticket number is: %d\n", data);
    close(fileDescriptor);
    
    semOp.sem_op = 1;//unlocking
    semop(semId, &semOp, 1);

    return 0;
}

