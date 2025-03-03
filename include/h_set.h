/*
    hash set

    v1.0
*/
#ifndef H_SET_H
#define H_SET_H

#include "h_map.h"

typedef struct
{
    HMap *map;
}
HSet;

/**
* create hash set
* 
* Parameters:
* - hc: calculate the hash code for the element
* - eq: compare whether the elements are equal
* 
* Returns:
* - hash set
*/
HSet *hs_new(hash_code hc, equals eq);

/**
* add the specified element
* 
* Parameters:
* - set: hash set
* - el: element
* 
* Returns:
* - success or failure
*/
bool hs_add(HSet *set, void *el);

/**
* remove the specified element
* 
* Parameters:
* - set: hash set
* - el: element
* 
* Returns:
* - success or failure
*/
bool hs_remove(HSet *set, void *el);

/**
* get all elements
* 
* Parameters:
* - set: hash set
* 
* Returns:
* - elements
*/
void **hs_els(HSet *set);

/**
* check if the hash set contains the specified element
* 
* Parameters:
* - set: hash set
* - el: element
* 
* Returns:
* - yes or no
*/
bool hs_cont(HSet *set, void *el);

/**
* traverse hash set
* 
* Parameters:
* - set: hash set
* - func: action on each element
*/
void hs_each(HSet *set, void (*func)(void *));

/**
* get the size of the hash set
* 
* Parameters:
* - set: hash set
* 
* Returns:
* - size
*/
size_t hs_size(HSet *set);

/**
* check if the hash set is empty
* 
* Parameters:
* - set: hash set
* 
* Returns:
* - yes or no
*/
bool hs_empty(HSet *set);

/**
* clear hash set
* 
* Parameters:
* - set: hash set
*/
void hs_clear(HSet *set);

/**
* free hash set
* 
* Parameters:
* - set: hash set address
*/
void hs_free(HSet **set);

#endif // !H_SET_H