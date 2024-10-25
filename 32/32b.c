/*
============================================================================
Name : 32b.c
Author : Naman Samant
Description : Write a program to implement semaphore to protect any critical section.
b. protect shared memory from concurrent write access
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024
union semun {
    int val; 
};

void lock(int semid) {
    struct sembuf sem_op = {0, -1, 0}; // Locking operation
    semop(semid, &sem_op, 1);
}

void unlock(int semid) {
    struct sembuf sem_op = {0, 1, 0}; // Unlocking operation
    semop(semid, &sem_op, 1);
}

int main() {
    key_t key = ftok("shmfile", 65); 
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666); 
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    union semun sem_attr;
    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork(); 
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        for (int i = 0; i < 5; i++) {
            lock(semid); 
            snprintf(data, SHM_SIZE, "Child process writing %d", i);
            printf("Child: %s\n", data);
            unlock(semid); 
            sleep(1); 
        }
    } else { 
        for (int i = 0; i < 5; i++) {
            lock(semid); 
            snprintf(data, SHM_SIZE, "Parent process writing %d", i);
            printf("Parent: %s\n", data);
            unlock(semid);
            sleep(1); 
        }
        
        wait(NULL);
        
        shmdt(data); 
        shmctl(shmid, IPC_RMID, NULL); 
        semctl(semid, 0, IPC_RMID); 
    }

    return 0;
}

