#include <unistd.h>
#include <stdio.h>
#include <time.h>

int global_val = 0;

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        printf("fork error\n");
    else if (pid == 0) {
        global_val++;
    } else {
        sleep(2);
    }

    printf("pid = %ld, global_val = %d\n", (long)getpid(), global_val);

    return 0;
}

