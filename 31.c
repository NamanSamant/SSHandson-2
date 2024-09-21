/*
============================================================================
Name : 31.c
Author : Naman Samant
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 21st Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *binary_semaphore_name = "/binary_semaphore";
    const char *counting_semaphore_name = "/counting_semaphore";
    sem_t *binary_sem = sem_open(binary_semaphore_name, O_CREAT | O_EXCL, 0644, 1);
    if (binary_sem == SEM_FAILED) {
        perror("sem_open (binary semaphore)");
        exit(EXIT_FAILURE);
    }
    printf("Binary semaphore created and initialized to 1.\n");
    sem_t *counting_sem = sem_open(counting_semaphore_name, O_CREAT | O_EXCL, 0644, 5);
    if (counting_sem == SEM_FAILED) {
        perror("sem_open (counting semaphore)");
        sem_close(binary_sem);
        sem_unlink(binary_semaphore_name);
        exit(EXIT_FAILURE);
    }
    printf("Counting semaphore created and initialized to 10.\n");
    sem_close(binary_sem);
    sem_close(counting_sem);
    sem_unlink(binary_semaphore_name);
    sem_unlink(counting_semaphore_name);
    return 0;
}

