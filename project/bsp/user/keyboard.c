/*
 * File name: keyboard.c
 */
#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <sys/select.h>
#include <sys/time.h>

int main(void){
    int fd;
    int ret;
    char *node = "/dev/input/event0";

    fd_set rfds;
    struct timeval tv;

    FD_ZERO(&rfds);

    if ((fd = open(node, O_RDWR | O_NDELAY)) < 0){
        printf("APP open %s failed", node);
        return 0;
    }

    FD_SET(fd, &rfds);

    while (1) {
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        ret = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
        if (ret < 0) {
            printf("select error\n");
            return 0;
        }

        if (FD_ISSET(fd, &rfds)) {
            struct input_event t;

            printf("select read able\n");
            read(fd, &t, sizeof(t));
            if (t.type == EV_KEY) {
                printf("key %d %s\n", t.code, (t.value) ? "Pressed" : "Released");
            }
        }
    }

    close(fd);
}
