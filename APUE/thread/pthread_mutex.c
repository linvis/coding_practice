#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

pthread_t demo_tid1;
pthread_t demo_tid2;

#define LOCK

#ifdef LOCK
pthread_mutex_t demo_mutex;
#endif

int count[10] = {0};

void *demo_func1(void *arg)
{
    int *p;
    while (1) {
#ifdef LOCK
        pthread_mutex_lock(&demo_mutex);
#endif

        for (int i = 0; i < 10; i++)
            count[i] = 1;

        printf("thread1 count: ");
        for (int i = 0; i < 10; i++)
            printf(" %d  ", count[i]);
        printf("\n");

#ifdef LOCK
        pthread_mutex_unlock(&demo_mutex);
#endif

        usleep(100 * 1000);
    }
}

void *demo_func2(void *arg)
{
    int tmp;
    while (1) {
#ifdef LOCK
        pthread_mutex_lock(&demo_mutex);
#endif


        for (int i = 0; i < 10; i++)
            count[i] = 2;

        usleep(1 * 1000);

        printf("thread2 count: ");
        for (int i = 0; i < 10; i++)
            printf(" %d  ", count[i]);
        printf("\n");

#ifdef LOCK
        pthread_mutex_unlock(&demo_mutex);
#endif

        usleep(100 * 1000);
    }
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

#ifdef LOCK
    pthread_mutex_init(&demo_mutex, NULL);
#endif

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
