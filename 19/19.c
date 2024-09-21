/*
============================================================================
Name : 19.c
Author : Naman Samant
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date: 21st Sep, 2024.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char *fifo1 = "./fifo_mkfifo";
    char *fifo2 = "./fifo_mknod";
    int status_mkfifo, status_mknod;
    status_mkfifo = mkfifo(fifo1, S_IRWXU);
    if (status_mkfifo == -1)
        perror("Error creating FIFO with mkfifo");
    else
        printf("FIFO created using mkfifo. Check with `ls -l`.\n");
    status_mknod = mknod(fifo2, __S_IFIFO | S_IRWXU, 0);
    if (status_mknod == -1)
        perror("Error creating FIFO with mknod");
    else
        printf("FIFO created using mknod. Check with `ls -l`.\n");

    return 0;
}
