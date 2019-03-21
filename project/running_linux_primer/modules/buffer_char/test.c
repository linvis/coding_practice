/*
 * File name: test.c
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DEVICE_DEV_NAME "/dev/buffer_char"

int main(void)
{
    char buffer[64];
    int fd;
    size_t len;
    char message[] = "testing the virtual FIFO device";
    char *read_buffer;
    int ret;

    len = sizeof(message) / sizeof(message[0]);

    fd = open(DEVICE_DEV_NAME, O_RDWR);
    if (fd < 0) {
        printf("open device %s failed\n", DEVICE_DEV_NAME);
        return -1;
    }

    ret = write(fd, message, len);
    if (ret != len) {
        printf("write fail\n");
        /* return -1; */
    }

    read_buffer = malloc(2 * len);
    memset(read_buffer, 0, 2 * len);

    close(fd);

    fd = open(DEVICE_DEV_NAME, O_RDWR);
    if (fd < 0) {
        printf("open device %s failed\n", DEVICE_DEV_NAME);
        return -1;
    }

    ret = read(fd, read_buffer, 2 * len);
    printf("read %d buffer\n", ret);
    printf("read buffer %s\n", read_buffer);

    close(fd);

    return 0;
}
