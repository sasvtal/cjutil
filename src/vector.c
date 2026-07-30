#include "vector.h"

#include <stdlib.h>

struct vtr
{
    void **data;

    size_t len;
    size_t size;
};

static bool grow(Vector *vec);



Vector *vtr_new(void)
{
    Vector *vec = malloc(sizeof(Vector));
    if (vec == NULL) return NULL;

    vec->data = NULL;

    vec->len = 0;
    vec->size = 0;

    return vec;
}

bool vtr_add(Vector *vec, void *el)
{
    size_t size = vec->size;

    if (size == vec->len && !grow(vec))
        return false;

    vec->data[size] = el;
    vec->size++;

    return true;
}

void *vtr_get(Vector *vec, size_t index)
{
    if (index >= vec->size) return NULL;

    return vec->data[index];
}

void *vtr_set(Vector *vec, size_t index, void *el)
{
    if (index >= vec->size) return NULL;

    void *old_el = vec->data[index];
    vec->data[index] = el;

    return old_el;
}

void *vtr_remove(Vector *vec, size_t index)
{
    if (index >= vec->size) return NULL;

    void **data = vec->data;
    void *el = data[index];

    size_t last = vec->size - 1;
    for (size_t i = index; i < last; ++i)
        data[i] = data[i + 1];

    data[last] = NULL;
    vec->size--;

    return el;
}

void vtr_for_each(Vector *vec, void (*action)(void *))
{
    void **data = vec->data;

    for (size_t i = 0, size = vec->size; i < size; ++i)
        action(data[i]);
}

size_t vtr_size(Vector *vec)
{
    return vec->size;
}

bool vtr_is_empty(Vector *vec)
{
    return vec->size == 0;
}

void vtr_clear(Vector *vec)
{
    void **data = vec->data;

    for (size_t i = 0, size = vec->size; i < size; ++i)
        data[i] = NULL;

    vec->size = 0;
}

void vtr_free(Vector **vec)
{
    if (*vec == NULL) return;

    free((*vec)->data);
    free(*vec);

    *vec = NULL;
}



static bool grow(Vector *vec)
{
    size_t len = vec->len;
    void **data;

    if (len == 0)
    {
        // init
        len = 10;
        data = malloc(len * sizeof(void *));
    }
    else
    {
        // grow
        len = len + (len >> 1);
        data = realloc(vec->data, len * sizeof(void *));
    }

    if (data == NULL) return false;

    for (size_t i = vec->size; i < len; ++i)
        data[i] = NULL;

    vec->data = data;
    vec->len = len;

    return true;
}