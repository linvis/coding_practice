/*
 * File name: server.c
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
#include <time.h>


#define SERV_PORT 1234

int main(void)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;

    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 100);

    for ( ; ; ) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

        if ((childpid = fork()) == 0) {
            char buf[128];
            close(listenfd);
            read(connfd, buf, 128);
            printf("%s\n", buf);
            exit(0);
        }
         close(connfd);
        
    }

    exit(0);
}
