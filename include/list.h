/*
    linked list
*/
#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct n
{
    struct n *prev;
    struct n *next;
    void *el;
}
Node;

typedef struct
{
    Node *head;
    Node *tail;
    int size;
}
List;

/*
    create a list
*/
List *ls_new(void);

/*
    add an element at the front of the list
*/
bool ls_left_push(List *list, void *el);

/*
    add an element at the end of the list
*/
bool ls_right_push(List *list, void *el);

/*
    remove the first element
*/
void *ls_left_pop(List *list);

/*
    remove the last element
*/
void *ls_right_pop(List *list);

/*
    get all elements as array
*/
void **ls_to_array(List *list, bool ltr);

/*
    traverse the list
*/
void ls_for_each(List *list, void (*action)(void *), bool ltr);

/*
    get the size of the list
*/
int ls_size(List *list);

/*
    check if the list is empty
*/
bool ls_is_empty(List *list);

/*
    clear the list
*/
void ls_clear(List *list);

/*
    free the list
*/
void ls_free(List **list);

#endif // !LIST_H