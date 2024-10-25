/*
============================================================================
Name : 32c.c
Author : Naman Samant
Description : Write a program to implement semaphore to protect any critical section.
c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_RESOURCES 2 
#define NUM_PROCESSES 5
union semun {
    int val;               
};

void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0}; 
    semop(semid, &sb, 1);
}

void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0};
    semop(semid, &sb, 1);
}

void access_resources(int process_id) {
    printf("Process %d is trying to access resources...\n", process_id);
    sleep(1); 
    printf("Process %d has accessed the resources.\n", process_id);
}

int main() {
    key_t key = ftok(".", 'S'); 
    int semid = semget(key, 1, IPC_CREAT | 0666); 
    union semun sem_union;
    sem_union.val = NUM_RESOURCES;
    semctl(semid, 0, SETVAL, sem_union);
    
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid_t pid = fork();
        if (pid == 0) { 
            sem_wait(semid); 
            access_resources(i);
            sem_signal(semid); 
            exit(0); 
        } else if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    semctl(semid, 0, IPC_RMID); 
    printf("All processes have finished executing.\n");

    return 0;
}

