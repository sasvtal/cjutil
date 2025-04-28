#include "list.h"

#include <stdlib.h>

/*
    create a node
*/
static Node *new_node(void *el);



List *ls_new(void)
{
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

bool ls_left_push(List *list, void *el)
{
    Node *head = list->head;

    Node *node = new_node(el);
    if (node == NULL) return false;

    node->next = head;

    if (head == NULL)
        // add the first node
        list->tail = node;
    else
        head->prev = node;

    list->head = node;
    list->size++;

    return true;
}

bool ls_right_push(List *list, void *el)
{
    Node *tail = list->tail;

    Node *node = new_node(el);
    if (node == NULL) return false;

    node->prev = tail;

    if (tail == NULL)
        // add the first node
        list->head = node;
    else
        tail->next = node;

    list->tail = node;
    list->size++;

    return true;
}

void *ls_left_pop(List *list)
{
    Node *head = list->head;
    if (head == NULL) return NULL;

    void *rem_el = head->el;
    list->head = head->next;

    if (head->next == NULL)
        // remove the last node
        list->tail = NULL;
    else
        head->next->prev = NULL;

    free(head);
    list->size--;

    return rem_el;
}

void *ls_right_pop(List *list)
{
    Node *tail = list->tail;
    if (tail == NULL) return NULL;

    void *rem_el = tail->el;
    list->tail = tail->prev;

    if (tail->prev == NULL)
        // remove the last node
        list->head = NULL;
    else
        tail->prev->next = NULL;

    free(tail);
    list->size--;

    return rem_el;
}

void **ls_to_array(List *list, bool ltr)
{
    void **arr = (void **)malloc(list->size * sizeof(void *));
    if (arr == NULL) return NULL;

    int index = 0;
    if (ltr)
        for (Node *n = list->head; n != NULL; n = n->next)
            arr[index++] = n->el;
    else
        for (Node *n = list->tail; n != NULL; n = n->prev)
            arr[index++] = n->el;

    return arr;
}

void ls_for_each(List *list, void (*action)(void *), bool ltr)
{
    if (ltr)
        for (Node *n = list->head; n != NULL; n = n->next)
            action(n->el);
    else
        for (Node *n = list->tail; n != NULL; n = n->prev)
            action(n->el);
}

int ls_size(List *list)
{
    return list->size;
}

bool ls_is_empty(List *list)
{
    return list->size == 0;
}

void ls_clear(List *list)
{
    for (Node *n = list->head; n != NULL;)
    {
        Node *curr = n;
        n = n->next;
        free(curr);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void ls_free(List **list)
{
    if (*list == NULL) return;

    ls_clear(*list);

    free(*list);

    *list = NULL;
}



static Node *new_node(void *el)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) return NULL;

    node->prev = NULL;
    node->next = NULL;
    node->el = el;

    return node;
}