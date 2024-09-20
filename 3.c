/*
============================================================================
Name : 3.c
Author : Naman Samant
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit limit;
    int resource = RLIMIT_CPU;
    if (getrlimit(resource, &limit) == 0) {
        limit.rlim_cur = 10;
        limit.rlim_max = 30;
        if (setrlimit(resource, &limit) == 0) {
            printf("Resource limit set successfully.\n");
        } else {
            perror("setrlimit");
        }
    } else {
        perror("getrlimit");
    }

    return 0;
}
