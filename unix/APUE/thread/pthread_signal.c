#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

pthread_t demo_tid;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitlock = PTHREAD_COND_INITIALIZER;

int quitflag;
sigset_t mask;

void *demo_func(void *arg)
{
    int err, signo;

    for ( ; ; ) {
        err = sigwait(&mask, &signo);
        if (err != 0) {
            printf("wait signal err\n");
            exit(0);
        }

        switch (signo) {
        case SIGINT:
            /* Ctrl  C */
            printf("\ninterrupt\n");
            break;
        case SIGQUIT:
            /* Ctrl \ */
            printf("\nquit\n");
            pthread_mutex_lock(&lock);
            quitflag = 1;
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&waitlock);
            return (0);
        default:
            printf("unexcept signal\n");
            exit(1);
        }
    }
}

int main(void)
{
    int err = 0;

    sigset_t oldmask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);

    if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0) {
        printf("SIG_BLOCK error");
        exit(0);
    }

    err = pthread_create(&demo_tid, NULL, demo_func, NULL);
    if (err != 0)
        printf("err, can't create thread\n");

    pthread_mutex_lock(&lock);
    while (quitflag == 0)
        pthread_cond_wait(&waitlock, &lock);
    pthread_mutex_unlock(&lock);

    quitflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("SIG_SETMASK error");

    exit(0);
}
