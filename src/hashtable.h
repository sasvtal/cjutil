#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct hst Hashtable;
typedef struct hse HashEntry;

Hashtable *hst_new(int (*hc)(void *), bool (*eq)(void *, void *));

void *hst_put(Hashtable *tab, void *key, void *value);

void *hst_get(Hashtable *tab, void *key);

void *hst_remove(Hashtable *tab, void *key);

bool hst_contains_key(Hashtable *tab, void *key);

HashEntry *hst_iter_first(Hashtable *tab);

HashEntry *hst_iter_next(Hashtable *tab);

void hst_for_each(Hashtable *tab, void (*action)(void *, void *));

size_t hst_size(Hashtable *tab);

bool hst_is_empty(Hashtable *tab);

void hst_clear(Hashtable *tab);

void hst_free(Hashtable **tab);

void *hse_get_key(HashEntry *entry);

void *hse_get_value(HashEntry *entry);

void *hse_set_value(HashEntry *entry, void *value);

#endif // !HASHTABLE_H