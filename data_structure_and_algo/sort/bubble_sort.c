/*
 * File name: bubble_sort.c
 */

#include <stdio.h>
#include <stdint.h>

void bubble_sort(int *data, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < (size - 1); j++) {
            if (data[j] > data[j + 1]) {
                int tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}


int main(void)
{

    int data[20] = {1, 6, 2, 7, -10, 0, 11, 4, 20, 5, 13, -1, 22, 8, 14, 17, -22, 32, 19, 20};

    bubble_sort(data, sizeof(data) / sizeof(data[0]));

    printf("sort data: ");
    for (int i = 0; i < (int)(sizeof(data) / sizeof(data[0])); i++)
        printf("%d ", data[i]);
    printf("\n");

    return 0;
}
