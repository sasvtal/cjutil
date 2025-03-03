#include "l_list.h"

/**
* create node
*/
static Node *new_node(void *el);



LList *ll_new(void)
{
    LList *list = (LList *)malloc(sizeof(LList));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

bool ll_push(LList *list, void *el)
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

bool ll_rpush(LList *list, void *el)
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

void *ll_pop(LList *list)
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

void *ll_rpop(LList *list)
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

void **ll_els(LList *list, bool ltr)
{
    void **els = (void **)malloc(list->size * sizeof(void *));
    if (els == NULL) return NULL;

    size_t index = 0;
    if (ltr)
        for (Node *n = list->head; n != NULL; n = n->next)
            els[index++] = n->el;
    else
        for (Node *n = list->tail; n != NULL; n = n->prev)
            els[index++] = n->el;

    return els;
}

void ll_each(LList *list, void (*func)(void *), bool ltr)
{
    if (ltr)
        for (Node *n = list->head; n != NULL; n = n->next)
            func(n->el);
    else
        for (Node *n = list->tail; n != NULL; n = n->prev)
            func(n->el);
}

size_t ll_size(LList *list)
{
    return list->size;
}

bool ll_empty(LList *list)
{
    return list->size == 0;
}

void ll_clear(LList *list)
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

void ll_free(LList **list)
{
    if (*list == NULL) return;

    ll_clear(*list);

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