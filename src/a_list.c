#include "a_list.h"

/**
* grow array list
*/
static bool grow(AList *list);



AList *al_new(void)
{
    AList *list = (AList *)malloc(sizeof(AList));
    if (list == NULL) return NULL;

    list->data = NULL;
    list->len = 0;
    list->size = 0;

    return list;
}

bool al_add(AList *list, void *el)
{
    size_t size = list->size;
    if (size == list->len && !grow(list)) return false;

    list->data[size] = el;
    list->size++;

    return true;
}

void *al_get(AList *list, size_t index)
{
    if (index >= list->size) return NULL;

    return list->data[index];
}

void *al_set(AList *list, size_t index, void *el)
{
    if (index >= list->size) return NULL;

    void *old_el = list->data[index];
    list->data[index] = el;

    return old_el;
}

void *al_remove(AList *list, size_t index)
{
    if (index >= list->size) return NULL;

    void **data = list->data;
    void *rem_el = data[index];
    size_t last = list->size - 1;

    for (size_t i = index; i < last; i++)
        data[i] = data[i + 1];

    data[last] = NULL;
    list->size--;

    return rem_el;
}

void al_each(AList *list, void (*func)(void *))
{
    void **data = list->data;
    for (size_t i = 0; i < list->size; i++)
        func(data[i]);
}

size_t al_size(AList *list)
{
    return list->size;
}

bool al_empty(AList *list)
{
    return list->size == 0;
}

void al_clear(AList *list)
{
    void **data = list->data;
    for (size_t i = 0; i < list->size; i++)
        data[i] = NULL;

    list->size = 0;
}

void al_free(AList **list)
{
    if (*list == NULL) return;

    free((*list)->data);
    free(*list);

    *list = NULL;
}



static bool grow(AList *list)
{
    size_t len = list->len;
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
        data = (void **)realloc(list->data, len * sizeof(void *));
    }

    if (data == NULL) return false;

    list->data = data;
    list->len = len;

    return true;
}