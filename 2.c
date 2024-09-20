/*
============================================================================
Name : 2.c
Author : Naman Samant
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 20th Sep, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit limit;
    int res;

    for (res = RLIMIT_CPU; res <= RLIMIT_NPROC; res++) {
        if (getrlimit(res, &limit) == 0) {
            printf("Resource: %d\n", res);
            printf("Soft limit: %ld\n", limit.rlim_cur);
            printf("Hard limit: %ld\n\n", limit.rlim_max);
        } else {
            perror("getrlimit");
        }
    }

    return 0;
}
