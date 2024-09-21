/*
============================================================================
Name : 30.c
Author : Naman Samant
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *data;
    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    snprintf(data, SHM_SIZE, "Hello, Shared Memory!");
    printf("Data written to shared memory: %s\n", data);
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    data = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    // Attempt to overwrite (this should fail since we're in read-only mode)
    printf("Attempting to overwrite shared memory...\n");
    snprintf(data, SHM_SIZE, "Trying to overwrite!");
    printf("Data in shared memory: %s\n", data);
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory removed successfully.\n");
    return 0;
}

