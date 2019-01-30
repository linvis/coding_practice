/*
 * File name: empty_sizeof.c
 */
#include <stdio.h>

struct list {

};

int main(void)
{
    struct list l1[10];
    int a[10];
    printf("%d\n", sizeof(&a[0]));
}
