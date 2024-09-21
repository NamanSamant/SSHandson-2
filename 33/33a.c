/*
============================================================================
Name : 33a.c
Author : Naman Samant
Description : Write a program to communicate between two machines using socket.
Date: 21st Sep, 2024.
============================================================================
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char dataReceivedFromServer[100];
    ssize_t n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }
    n = read(sockfd, dataReceivedFromServer, sizeof(dataReceivedFromServer));
    if (n < 0) {
        perror("Reading from socket failed");
    } else {
        printf("Message : %s\n", dataReceivedFromServer);
    }
    write(sockfd, "Data from client", 16);
    close(sockfd);
    return 0;
}
