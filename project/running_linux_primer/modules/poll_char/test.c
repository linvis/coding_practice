/*
 * File name: test.c
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <errno.h>

int main(void)
{
    int ret;
	struct pollfd fds[2];
	char buffer0[64];
	char buffer1[64];

    fds[0].fd = open("/dev/buffer_char0", O_RDWR);
	if (fds[0].fd == -1) 
		goto fail;

	fds[0].events = POLLIN;

	fds[1].fd = open("/dev/buffer_char1", O_RDWR);
	if (fds[1].fd == -1) 
		goto fail;
	fds[1].events = POLLIN;

	while (1) {
		ret = poll(fds, 2, -1);
		if (ret == -1)
			goto fail;

		if (fds[0].revents & POLLIN) {
			ret = read(fds[0].fd, buffer0, sizeof(buffer0));
			if (ret < 0)
				goto fail;
			printf("%s\n", buffer0);
		}

		if (fds[1].revents & POLLIN) {
			ret = read(fds[1].fd, buffer1, sizeof(buffer1));
			if (ret < 0)
				goto fail;

			printf("%s\n", buffer1);
		}
	}

fail:
	perror("poll test failed");
	exit(EXIT_FAILURE);
}
