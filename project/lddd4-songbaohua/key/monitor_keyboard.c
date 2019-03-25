/*
 * File name: monitor_keyboard.c
 */

#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/select.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/input.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define MAX_KEY_FD 128

int handle_key_event(int fd1, int fd2);

int main(void)
{
    int fd1, fd2;

    fd1 = open("/dev/input/event5", O_RDONLY);
    if (fd1 <= 0) {
        printf("can't open event5\n");
        return 0;
    }
    fd2 = open("/dev/input/event6", O_RDONLY);
    if (fd2 <= 0) {
        printf("can't open event6\n");
        return 0;
    }

    handle_key_event(fd1, fd2);

    close(fd1);
    close(fd2);

    return 0;
}

int handle_key_event(int fd1, int fd2)
{
    int ret;
    fd_set readfds;

    printf("%s\n", __func__);

    struct input_event t;
    struct timeval timeout; 
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    /* while (1)   */
    /* {   */
        /* if (read (fd, &t, sizeof (t)) == sizeof (t))   */
        /* {   */
            /* printf("ffffff\n"); */
            /* if (t.type == EV_KEY)   */
                /* if (t.value == 0 || t.value == 1)   */
                /* {   */
                    /* printf ("key %d %s\n", t.code,   */
                            /* (t.value) ? "Pressed" : "Released");   */
                    /* if(t.code==KEY_ESC)   */
                        /* break;   */
                /* }   */
        /* }   */
    /* }   */
    FD_ZERO(&readfds);
    FD_SET(fd1, &readfds);
    FD_SET(fd2, &readfds);
    while (1) {

        ret = select(MAX_KEY_FD + 1, &readfds, NULL, NULL, NULL);
        switch (ret) {
        case -1:
            exit(0);
        case 0:
            printf("timeout\n");
            break;
        default:

            /* if (FD_ISSET(fd, &readfds)) { */
            printf("receive a read event\n");
            /* } */
            break;
        }

    }

    return 0;
}
