/*
    array list

    v1.0
*/
#ifndef A_LIST_H
#define A_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    void **data;
    size_t len;
    size_t size;
}
AList;

/**
* create array list
* 
* Returns:
* - array list
*/
AList *al_new(void);

/**
* add an element
* 
* Parameters:
* - list: array list
* - el: element
* 
* Returns:
* - success or failure
*/
bool al_add(AList *list, void *el);

/**
* get an element by index
* 
* Parameters:
* - list: array list
* - index: element index
* 
* Returns:
* - element
*/
void *al_get(AList *list, size_t index);

/**
* set an element by index
* 
* Parameters:
* - list: array list
* - index: element index
* - el: new element
* 
* Returns:
* - old element
*/
void *al_set(AList *list, size_t index, void *el);

/**
* remove an element by index
* 
* Parameters:
* - list: array list
* - index: element index
* 
* Returns:
* - removed element
*/
void *al_remove(AList *list, size_t index);

/**
* traverse array list
* 
* Parameters:
* - list: array list
* - func: action on each element
*/
void al_each(AList *list, void (*func)(void *));

/**
* get the size of the array list
* 
* Parameters:
* - list: array list
* 
* Returns:
* - size
*/
size_t al_size(AList *list);

/**
* check if the array list is empty
* 
* Parameters:
* - list: array list
* 
* Returns:
* - yes or no
*/
bool al_empty(AList *list);

/**
* clear array list
* 
* Parameters:
* - list: array list
*/
void al_clear(AList *list);

/**
* free array list
* 
* Parameters:
* - list: array list address
*/
void al_free(AList **list);

#endif // !A_LIST_H