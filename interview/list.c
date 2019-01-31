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

int main(void)
{
    List_t *head = (List_t*)malloc(sizeof(List_t));
    head->next = NULL;

    list_insert(head, 123);

    list_insert(head, 455);

    list_remove(head, 455);

    list_traverse(head);
}
