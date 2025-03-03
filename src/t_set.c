#include "t_set.h"

/**
* recursion
* action on each node
*/
static void each_node(Node *root, void (*func)(void *));



#define V ((void *)1)

TSet *ts_new(compare cmp)
{
    TMap *map = tm_new(cmp);
    if (map == NULL) return NULL;

    TSet *set = (TSet *)malloc(sizeof(TSet));
    if (set == NULL)
    {
        tm_free(&map);
        return NULL;
    }

    set->map = map;

    return set;
}

bool ts_add(TSet *set, void *el)
{
    return tm_put(set->map, el, V);
}

bool ts_remove(TSet *set, void *el)
{
    return tm_remove(set->map, el) == V;
}

void **ts_els(TSet *set)
{
    return tm_kvs(set->map, true);
}

bool ts_cont(TSet *set, void *el)
{
    return tm_contk(set->map, el);
}

void ts_each(TSet *set, void (*func)(void *))
{
    each_node(set->map->root, func);
}

size_t ts_size(TSet *set)
{
    return tm_size(set->map);
}

bool ts_empty(TSet *set)
{
    return tm_empty(set->map);
}

void ts_clear(TSet *set)
{
    return tm_clear(set->map);
}

void ts_free(TSet **set)
{
    if (*set == NULL) return;

    tm_free(&((*set)->map));
    free(*set);

    *set = NULL;
}



static void each_node(Node *root, void (*func)(void *))
{
    if (root->left != NULL) each_node(root->left, func);

    func(root->key);

    if (root->right != NULL) each_node(root->right, func);
}