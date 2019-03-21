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

/*
 * If use mac OS as server, please pay attention:
 * the max count of socket connection is 128 as default.
 * use 'sudo sysctl -w kern.ipc.somaxconn=512' to change it.
 */

#define SERV_PORT 1234

int main(void)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    time_t cur_time;
    struct tm *p_tm;

    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 1000);

    for ( ; ; ) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

        if ((childpid = fork()) == 0) {
            char buf[128], read_buf[128];
            close(listenfd);

            read(connfd, read_buf, 128);
            time(&cur_time);
            p_tm = localtime(&cur_time);
            sprintf(buf, "current time is %s", asctime(p_tm)); 

            write(connfd, buf, 128);

            exit(0);
        }
         close(connfd);
        
    }

    exit(0);
}
