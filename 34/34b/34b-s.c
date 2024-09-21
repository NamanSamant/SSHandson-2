/*
============================================================================
Name : 34b-server.c
Author : Naman Samant
Description : Write a program to create a concurrent server.
b. use pthread_create
Date: 21st Sep, 2024.
============================================================================
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *handlerFunction(void *connfd_ptr) {
    int connfd = *(int*)connfd_ptr;
    free(connfd_ptr);
    char buff[1024];
    read(connfd, buff, sizeof(buff));
    printf("Client: %s\n", buff);
    write(connfd, "Data from server", 16);
    close(connfd);
    return NULL;
}

int main() {
    int sockfd, connfd;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientLen;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
    bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(sockfd, 5);
    while (1) {
        clientLen = sizeof(clientAddress);
        connfd = accept(sockfd, (struct sockaddr*)&clientAddress, &clientLen);
        pthread_t thread;
        int *connfd_ptr = malloc(sizeof(int));
        *connfd_ptr = connfd;
        pthread_create(&thread, NULL, handlerFunction, connfd_ptr);
    }
    return 0;
}
