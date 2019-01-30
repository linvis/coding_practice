/*
 * File name: replace_char.c
 */
#include "stdio.h"

char *replace(char *string)
{
    if (string == NULL)
        return NULL;

    int blank = 0;
    int len = strlen(string);

    for (int i = 0; i < len; i++) {
        if (string[i] == ' ')
            blank++;
    }

    int tail = len + 2 * blank - 1;
    for (int i = len - 1; i > 0; i--) {
        if (string[i] == ' ') {
            string[tail--] = '0';
            string[tail--] = '2';
            string[tail--] = '%';
        } else
            string[tail--] = string[i];
    }

    return string;
}


int main(void)
{
    char string[50] = "we are happy";
    char *re;

    re = replace(string);

    printf("%s\n", re);
}
