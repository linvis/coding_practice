#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t demo_tid1;
pthread_t demo_tid2;

void *demo_func1(void *arg)
{
    printf("thread1 return\n");

    return((void*)1);
}

void *demo_func2(void *arg)
{
    printf("thread2 exit\n");

    pthread_exit((void*)2);
}

int main(void)
{
    int err = 0;
    void *tret;

    err = pthread_create(&demo_tid1, NULL, demo_func1, NULL);
    if (err != 0)
        printf("err, can't create thread1\n");

    err = pthread_create(&demo_tid2, NULL, demo_func2, NULL);
    if (err != 0)
        printf("err, can't create thread2\n");

    err = pthread_join(demo_tid1, &tret);
    if (err != 0)
        printf("err, can't join thread1\n");
    printf("thread1 exit code %ld\n", (long)tret);

    err = pthread_join(demo_tid2, &tret);
    if (err != 0)
        printf("err, can't join thread2\n");
    printf("thread2 exit code %ld\n", (long)tret);

    return 0;
}
