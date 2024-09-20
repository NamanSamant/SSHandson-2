/*
============================================================================
Name : 6.c
Author : Naman Samant
Description : Write a simple program to create three threads.
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

void *thread_function(void *arg) {
    printf("Hello from thread %ld\n", (intptr_t)arg);
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, thread_function, (void *)1);
    pthread_create(&thread2, NULL, thread_function, (void *)2);
    pthread_create(&thread3, NULL, thread_function, (void *)3);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("All threads have finished\n");

    return 0;
}
