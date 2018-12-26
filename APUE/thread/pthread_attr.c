#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * This demo doesn't work fine on Mac OS, but works on Linux
 * Mac OS
 * malloc addr: 0x7fb911800000
 * hello world, a new thread
 * thread stack addr: 0xffffffffffffb000, size is 20480
 * thread stack size is 20480
 *
 * Linux
 * malloc addr: 0x563b91a1f010
 * thread stack addr: 0x563b91a1f010, size is 25600
 * thread stack size is 25600
 * hello world, a new thread
 */

pthread_t demo_tid;

void *demo_func(void *arg)
{
    printf("hello world, a new thread\n");

    return((void*)0);
}

int main(void)
{
    int err = 0;
    size_t stacksize;
    void *cus_stack;
    void *read_stack;

    pthread_attr_t attr;

    err = pthread_attr_init(&attr);
    if (err != 0)
        return err;

    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    err = pthread_attr_setstacksize(&attr, 20480);

    cus_stack = malloc(25600);
    printf("malloc addr: %p\n", cus_stack);

    err = pthread_attr_setstack(&attr, cus_stack, 25600);

    err = pthread_create(&demo_tid, &attr, demo_func, NULL);
    if (err != 0)
        printf("err, can't create thread\n");

    err = pthread_attr_getstack(&attr, &read_stack, &stacksize);
    printf("thread stack addr: %p, size is %ld\n", read_stack, stacksize);

    err= pthread_attr_getstacksize(&attr, &stacksize);
    printf("thread stack size is %ld\n", stacksize);

    pthread_attr_destroy(&attr);

    sleep(1);

    return 0;
}

