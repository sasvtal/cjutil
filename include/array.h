/*
    dynamic array
*/
#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct
{
    void **data;
    int len;
    int size;
}
Array;

/*
    create an array
*/
Array *ar_new(void);

/*
    add an element
*/
bool ar_add(Array *arr, void *el);

/*
    get an element by index
*/
void *ar_get(Array *arr, int index);

/*
    set an element by index
*/
void *ar_set(Array *arr, int index, void *el);

/*
    remove an element by index
*/
void *ar_remove(Array *arr, int index);

/*
    traverse the array
*/
void *ar_for_each(Array *arr, void (*action)(void *));

/*
    get the size of the array
*/
int ar_size(Array *arr);

/*
    check if the array is empty
*/
bool ar_is_empty(Array *arr);

/*
    clear the array
*/
void ar_clear(Array *arr);

/*
    free the array
*/
void ar_free(Array **arr);

#endif // !ARRAY_H