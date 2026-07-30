#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct vtr Vector;

Vector *vtr_new(void);

bool vtr_add(Vector *vec, void *el);

void *vtr_get(Vector *vec, size_t index);

void *vtr_set(Vector *vec, size_t index, void *el);

void *vtr_remove(Vector *vec, size_t index);

void vtr_for_each(Vector *vec, void (*action)(void *));

size_t vtr_size(Vector *vec);

bool vtr_is_empty(Vector *vec);

void vtr_clear(Vector *vec);

void vtr_free(Vector **vec);

#endif // !VECTOR_H