/*
 * File name: test.c
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_DEV_NAME "/dev/simple_char"

int main(void)
{
    char buffer[64];
    int fd;

    fd = open(DEVICE_DEV_NAME, O_RDONLY);
    if (fd < 0) {
        printf("open device %s failed\n", DEVICE_DEV_NAME);
        return -1;
    }

    read(fd, buffer, 64);
    close(fd);

    return 0;
}
