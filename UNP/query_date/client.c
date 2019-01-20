/*
 * File name: client.c
 */
/* socket */
#include <sys/socket.h>
/* #include <netinet/in.h> */
/* inet_pton */
#include <arpa/inet.h>
/* printf */
#include <stdio.h>
/* exit */
#include <stdlib.h>
/* memset */
#include <string.h>
/* write */
#include <unistd.h>


#define SERV_PORT 1234

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        printf("type server address\n");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    write(sockfd, "query date", sizeof("query date"));

    exit(0);
}
