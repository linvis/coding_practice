/*
 * File name: merge_sort.c
 */

#include "stdio.h"
#include "stdlib.h"

void m_sort(int *data, int *tmp, int left, int right)
{
    if (left >= right)
        return;

    int center = (left + right) / 2;

    m_sort(data, tmp, left, center);
    m_sort(data, tmp, center + 1, right);

    int l_pos = left;
    int r_pos = center + 1;
    int tmp_pos = left;

    while (l_pos <= center && r_pos <= right) {
        if (data[l_pos] <= data[r_pos])
            tmp[tmp_pos++] = data[l_pos++];
        else
            tmp[tmp_pos++] = data[r_pos++];
    }

    while(l_pos <= center)
        tmp[tmp_pos++] = data[l_pos++];

    while(r_pos <= right)
        tmp[tmp_pos++] = data[r_pos++];

    for (int i = left; i <= right; i ++)
        data[i] = tmp[i];
}

void merge_sort(int *data, int size)
{
    int *tmp = malloc(size * sizeof(int));

    if (tmp == NULL) {
        printf("fatal, can't malloc\n");
        return;
    }

    m_sort(data, tmp, 0, size - 1);
    free(tmp);
}

int main(void)
{

    int data[20] = {1, 6, 2, 7, -10, 0, 11, 4, 20, 5, 13, -1, 22, 8, 14, 17, -22, 32, 19, 20};

    merge_sort(data, sizeof(data) / sizeof(data[0]));

    printf("sort data: ");
    for (int i = 0; i < (int)(sizeof(data) / sizeof(data[0])); i++)
        printf("%d ", data[i]);
    printf("\n");

    return 0;
}
