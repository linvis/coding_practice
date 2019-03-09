/*
 * File name: quick_sort.c
 */
#include <stdio.h>
#include <stdint.h>

void swap(int *a, int *b)
{
    int tmp = *b;
    
    *b = *a;
    *a = tmp;
}

int median3(int *data, unsigned long left, unsigned long right)
{
    int center = (left + right) / 2;

    if (data[left] > data[center])
        swap(&data[left], &data[center]);

    if (data[center] > data[right])
        swap(&data[center], &data[right]);

    if (data[left] > data[right])
        swap(&data[left], &data[right]);

    swap(&data[center], &data[right]);

    return data[right];
}

void q_sort(int *data, int left, int right)
{
    int pivot;

    if (left >= right)
        return;

    pivot = median3(data, left, right);
    /* pivot = data[right]; */

    int i = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (data[j] <= pivot) {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[right]);

    q_sort(data, left, i);
    q_sort(data, i + 2, right);
}

void quick_sort(int *data, unsigned long size)
{
    q_sort(data, 0, size - 1);
}

int main(void)
{
    int data[20] = {1, 6, 2, 7, -10, 0, 11, 4, 20, 5, 13, -1, 22, 8, 14, 17, -22, 32, 19, 20};
    /* int data[3] = {1, 6, 2};  */

    quick_sort(data, sizeof(data) / sizeof(data[0]));

    printf("sort data: ");
    for (unsigned long i = 0; i < (sizeof(data) / sizeof(data[0])); i++)
        printf("%d ", data[i]);
    printf("\n");

    return 0;
}
