#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

pthread_t demo_tid;
pthread_mutex_t mutex;

/*#define MUTEX_RECURSIVE*/

void *demo_func(void *arg)
{
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);

    printf("hello world, a new thread\n");

    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);

    return((void*)0);
}

int main(void)
{
    int err = 0;

#ifdef MUTEX_RECURSIVE
    pthread_mutexattr_t attr;

    err = pthread_mutexattr_init(&attr);

    err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    err = pthread_mutex_init(&mutex, &attr);
#else

    err = pthread_mutex_init(&mutex, NULL);
#endif

    err = pthread_create(&demo_tid, NULL, demo_func, NULL);
    if (err != 0)
        printf("err, can't create thread\n");

#ifdef MUTEX_RECURSIVE
    err = pthread_mutexattr_destroy(&attr);
#endif

    sleep(1);

    return 0;
}

