/*
    linked list

    v1.0
*/
#ifndef L_LIST_H
#define L_LIST_H

#include <stdlib.h>
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
    size_t size;
}
LList;

/**
* create linked list
* 
* Returns:
* - linked list
*/
LList *ll_new(void);

/**
* add an element at the front of the linked list
* 
* Parameters:
* - list: linked list
* - el: element
* 
* Returns:
* - success or failure
*/
bool ll_push(LList *list, void *el);

/**
* add an element at the end of the linked list
* 
* Parameters:
* - list: linked list
* - el: element
* 
* Returns:
* - success or failure
*/
bool ll_rpush(LList *list, void *el);

/**
* remove the first element
* 
* Parameters:
* - list: linked list
* 
* Returns:
* - first element
*/
void *ll_pop(LList *list);

/**
* remove the last element
* 
* Parameters:
* - list: linked list
* 
* Returns:
* - last element
*/
void *ll_rpop(LList *list);

/**
* get all elements
* 
* Parameters:
* - list: linked list
* - ltr: left to right
* 
* Returns:
* - elements
*/
void **ll_els(LList *list, bool ltr);

/**
* traverse linked list
* 
* Parameters:
* - list: linked list
* - func: action on each element
* - ltr: left to right
*/
void ll_each(LList *list, void (*func)(void *), bool ltr);

/**
* get the size of the linked list
* 
* Parameters:
* - list: linked list
* 
* Returns:
* - size
*/
size_t ll_size(LList *list);

/**
* check if the linked list is empty
* 
* Parameters:
* - list: linked list
* 
* Returns:
* - yes or no
*/
bool ll_empty(LList *list);

/**
* clear linked list
* 
* Parameters:
* - list: linked list
*/
void ll_clear(LList *list);

/**
* free linked list
* 
* Parameters:
* - list: linked list address
*/
void ll_free(LList **list);

#endif // !L_LIST_H