/*
    tree set

    v1.0
*/
#ifndef T_SET_H
#define T_SET_H

#include "t_map.h"

typedef struct
{
    TMap *map;
}
TSet;

/**
* create tree set
* 
* Parameters:
* - cmp: compare elements
*        e1 < e2 rtn n < 0
*        e1 = e2 rtn 0
*        e1 > e2 rtn n > 0
* 
* Returns:
* - tree set
*/
TSet *ts_new(compare cmp);

/**
* add the specified element
* 
* Parameters:
* - set: tree set
* - el: element
* 
* Returns:
* - success or failure
*/
bool ts_add(TSet *set, void *el);

/**
* remove the specified element
* 
* Parameters:
* - set: tree set
* - el: element
* 
* Returns:
* - success or failure
*/
bool ts_remove(TSet *set, void *el);

/**
* get all elements
* 
* Parameters:
* - set: tree set
* 
* Returns:
* - elements
*/
void **ts_els(TSet *set);

/**
* check if the tree set contains the specified element
* 
* Parameters:
* - set: tree set
* - el: element
* 
* Returns:
* - yes or no
*/
bool ts_cont(TSet *set, void *el);

/**
* traverse tree set
* 
* Parameters:
* - set: tree set
* - func: action on each element 
*/
void ts_each(TSet *set, void (*func)(void *));

/**
* get the size of the tree set
* 
* Parameters:
* - set: tree set
* 
* Returns:
* - size
*/
size_t ts_size(TSet *set);

/**
* check if the tree set is empty
* 
* Parameters:
* - set: tree set
* 
* Returns:
* - yes or no
*/
bool ts_empty(TSet *set);

/**
* clear tree set
* 
* Parameters:
* - set: tree set
*/
void ts_clear(TSet *set);

/**
* free tree set
* 
* Parameters:
* - set: tree set address
*/
void ts_free(TSet **set);

#endif // !T_SET_H