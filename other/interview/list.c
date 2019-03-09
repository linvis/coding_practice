/*
 * File name: list.c
 */
#include <stdio.h>
#include <string.h>

typedef struct List {
    int element;
    struct List *next;
} List_t;

int list_insert(List_t *head, int val)
{
    List_t *pnew = (List_t*)malloc(sizeof(List_t));

    pnew->element = val;
    pnew->next = NULL;

    if (pnew == NULL)
        return -1;

    List_t *pnode = head;

    while (pnode->next) {
        pnode = pnode->next;
    }
    pnode->next = pnew;

    return 0;
}

int list_remove(List_t *head, int val)
{
    List_t *pnode = head;

    while(pnode->next) {
        if (pnode->next->element == val) {
            pnode->next = pnode->next->next;
            break;
        } else
            pnode = pnode->next;
    }

    return 0;
}

int list_traverse(List_t *head)
{
    if (head == NULL)
        return -1;
    else {
        List_t *pnode = head->next;

        while (pnode) {
            printf("%d ", pnode->element);
            pnode = pnode->next;
        }
    }

}

void list_traverse_from_tail(List_t *head)
{
    if (head->next) {
        list_traverse_from_tail(head->next);
    }
    printf("%d ", head->element);
}

int main(void)
{
    List_t *head = (List_t*)malloc(sizeof(List_t));
    head->next = NULL;

    list_insert(head, 123);

    list_insert(head, 455);

    /* list_remove(head, 455); */

    printf("traverse list: ");
    list_traverse(head);
    printf("\n");

    printf("traverse list from tail: ");
    list_traverse_from_tail(head->next);
    printf("\n");
}
