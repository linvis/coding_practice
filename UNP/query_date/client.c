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
#include <pthread.h>


#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 1234

pthread_mutex_t id_mutex;
int thread_id = 0;

void *query_date(void *arg)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_ADDR, &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    write(sockfd, "query date", sizeof("query date"));

    char read_buf[128];

    read(sockfd, read_buf, 128);
    close(sockfd);

    pthread_mutex_lock(&id_mutex);

    printf("thread %3d query time is %s", ++thread_id, read_buf);

    pthread_mutex_unlock(&id_mutex);

    return((void*)0);
}

/* int main(int argc, char **argv) */
int main(void)
{

    /* if (argc != 2) { */
        /* printf("type server address\n"); */
        /* exit(0); */
    /* } */

     pthread_mutex_init(&id_mutex, NULL);

    for (int i = 0; i < 500; i++) {
        pthread_t pid;
        pthread_create(&pid, NULL, query_date, NULL);
    }

    sleep(2);
}
