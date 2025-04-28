#include "array.h"

#include <stdlib.h>

/*
    grow the array
*/
static bool grow(Array *arr);



Array *ar_new(void)
{
    Array *arr = (Array *)malloc(sizeof(Array));
    if (arr == NULL) return NULL;

    arr->data = NULL;
    arr->len = 0;
    arr->size = 0;

    return arr;
}

bool ar_add(Array *arr, void *el)
{
    int size = arr->size;
    if (size == arr->len && !grow(arr))
        return false;

    arr->data[size] = el;
    arr->size++;

    return true;
}

void *ar_get(Array *arr, int index)
{
    if (index < 0 || index >= arr->size)
        return NULL;

    return arr->data[index];
}

void *ar_set(Array *arr, int index, void *el)
{
    if (index < 0 || index >= arr->size)
        return NULL;

    void *old_el = arr->data[index];
    arr->data[index] = el;

    return old_el;
}

void *ar_remove(Array *arr, int index)
{
    if (index < 0 || index >= arr->size)
        return NULL;

    void **data = arr->data;
    void *rem_el = data[index];
    int last = arr->size - 1;

    for (int i = index; i < last; i++)
        data[i] = data[i + 1];

    data[last] = NULL;
    arr->size--;

    return rem_el;
}

void *ar_for_each(Array *arr, void (*action)(void *))
{
    void **data = arr->data;
    int size = arr->size;

    for (int i = 0; i < size; i++)
        action(data[i]);
}

int ar_size(Array *arr)
{
    return arr->size;
}

bool ar_is_empty(Array *arr)
{
    return arr->size == 0;
}

void ar_clear(Array *arr)
{
    void **data = arr->data;
    int size = arr->size;

    for (int i = 0; i < size; i++)
        data[i] = NULL;

    arr->size = 0;
}

void ar_free(Array **arr)
{
    if (*arr == NULL) return;

    free((*arr)->data);
    free(*arr);

    *arr = NULL;
}



static bool grow(Array *arr)
{
    int len = arr->len;
    void **data;

    if (len == 0)
    {
        // init
        len = 10;
        data = (void **)malloc(len * sizeof(void *));
    }
    else
    {
        // grow
        len = len + (len >> 1);
        data = (void **)realloc(arr->data, len * sizeof(void *));
    }

    if (data == NULL) return false;

    arr->data = data;
    arr->len = len;

    return true;
}