#include "h_set.h"

#define V ((void *)1)

HSet *hs_new(hash_code hc, equals eq)
{
    HMap *map = hm_new(hc, eq);
    if (map == NULL) return NULL;

    HSet *set = (HSet *)malloc(sizeof(HSet));
    if (set == NULL)
    {
        hm_free(&map);
        return NULL;
    }

    set->map = map;

    return set;
}

bool hs_add(HSet *set, void *el)
{
    return hm_put(set->map, el, V);
}

bool hs_remove(HSet *set, void *el)
{
    return hm_remove(set->map, el) == V;
}

void **hs_els(HSet *set)
{
    return hm_kvs(set->map, true);
}

bool hs_cont(HSet *set, void *el)
{
    return hm_contk(set->map, el);
}

void hs_each(HSet *set, void (*func)(void *))
{
    size_t len = set->map->len;
    Entry **table = set->map->table;

    for (size_t i = 0; i < len; i++)
        for (Entry *e = table[i]; e != NULL; e = e->next)
            func(e->key);
}

size_t hs_size(HSet *set)
{
    return hm_size(set->map);
}

bool hs_empty(HSet *set)
{
    return hm_empty(set->map);
}

void hs_clear(HSet *set)
{
    return hm_clear(set->map);
}

void hs_free(HSet **set)
{
    if (*set == NULL) return;

    hm_free(&((*set)->map));
    free(*set);

    *set = NULL;
}