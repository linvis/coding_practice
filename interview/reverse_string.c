/*
 * File name: reverse_string.c
 */

#include "stdio.h"

char *reverse(char *string)
{
    if (string == NULL)
		    return NULL;
    
		int len = strlen(string);
    
    for (int i = 0; i < len / 2; i++) {
	      char tmp;
        tmp = string[i];
        string[i] = string[len - 1 - i];
        string[len - 1 - i] = tmp;
    }
    
    return string;
}

int main(void)
{
    char string[] = "hello world";
    char *re;

    re = reverse(string);

    printf("%s\n", re);
}
