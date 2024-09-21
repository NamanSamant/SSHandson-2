/*
============================================================================
Name : 34a-client.c
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

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);
    connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    write(sockfd, "Data from client", 16);
    char buff[1024];
    read(sockfd, buff, sizeof(buff));
    printf("Server: %s\n", buff);
    close(sockfd);

    return 0;
}
