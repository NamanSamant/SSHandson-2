/*
============================================================================
Name : 33b.c
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
    int sockfd, newsockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char dataReceivedFromClient[100];
    ssize_t n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    listen(sockfd, 2);
    len = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if (newsockfd < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    write(newsockfd, "Data from server", 16);
    n = read(newsockfd, dataReceivedFromClient, sizeof(dataReceivedFromClient));
    if (n > 0) {
        printf("Message : %s\n", dataReceivedFromClient);
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
