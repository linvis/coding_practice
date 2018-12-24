#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t demo_tid;

void *demo_func(void *arg)
{
    printf("hello world, a new thread\n");

    return((void*)0);
}

int main(void)
{
    int err = 0;

    err = pthread_create(&demo_tid, NULL, demo_func, NULL);
    if (err != 0)
        printf("err, can't create thread\n");

    sleep(1);

    return 0;
}
