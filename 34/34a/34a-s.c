/*
============================================================================
Name : 34a-server.c
Author : Naman Samant
Description : Write a program to create a concurrent server.
a. use fork
Date: 21st Sep, 2024.
============================================================================
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int sockfd, connfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);
    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(sockfd, 5);
    while (1) {
        clientLen = sizeof(clientAddr);
        connfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientLen);
        if (fork() == 0) {
            char buff[1024];
            int bytes_read = read(connfd, buff, sizeof(buff) - 1);
            buff[bytes_read] = '\0';  // Add null terminator after reading
            printf("Client: %s\n", buff);
            write(connfd, "Data from server", 16);
            close(connfd);
            exit(0);
        }
        close(connfd);
    }
    return 0;
}
