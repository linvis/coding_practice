/*
 * File name: find_k_node_from_end.c
 */
#include <stdio.h>

typedef struct list {
    int element;
    struct list *next;
} list_t;

list_t* find_tail_k_node(list_t *head, int k)
{
    if (k <= 0)
        return NULL;

    if (head == NULL)
        return NULL;

    list_t *p_head = head, *p_tail = head;
    int n = k - 1;

    while(p_head->next) {
        p_head = p_head->next;
        n--;
        if (n < 0) {
            p_tail = p_tail->next;
        }
    }

    if (n > 0)
        return NULL;

    return p_tail;
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
int main(void)
{
    list_t test[5];
    int i;

    for(i = 0; i < ARRAY_SIZE(test) - 1; i++) {
        test[i].element = i;
        test[i].next = &test[i + 1];
    }
    test[i].element = i;
    test[i].next = NULL;

    list_t *k_node = find_tail_k_node(&test[0], 6);
    if (k_node)
        printf("%d \n", k_node->element);
    else
        printf("NULL\n");


    return 0;
}

