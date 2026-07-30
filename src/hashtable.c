#include "hashtable.h"

#include <stdlib.h>
#include <limits.h>

struct hst
{
    HashEntry **table;

    int (*hc)(void *);
    bool (*eq)(void *, void *);

    size_t len;
    size_t size;

    size_t iter_index;
    HashEntry *iter_entry;
};

struct hse
{
    int hash;

    void *key;
    void *value;

    HashEntry *next;
};

static bool init(Hashtable *tab, size_t len);

static HashEntry *find(Hashtable *tab, int hash, void *key, size_t index);

static bool rehash(Hashtable *tab);

static void add_entry(Hashtable *tab, HashEntry *entry, size_t index);



Hashtable *hst_new(int (*hc)(void *), bool (*eq)(void *, void *))
{
    Hashtable *tab = malloc(sizeof(Hashtable));
    if (tab == NULL) return NULL;

    if (!init(tab, 11))
    {
        free(tab);

        return NULL;
    }

    tab->hc = hc;
    tab->eq = eq;

    tab->iter_index = 0;
    tab->iter_entry = NULL;

    return tab;
}

void *hst_put(Hashtable *tab, void *key, void *value)
{
    int hash = tab->hc(key);
    size_t index = (hash & INT_MAX) % tab->len;

    HashEntry *entry = find(tab, hash, key, index);

    // set
    if (entry != NULL) return hse_set_value(entry, value);

    // 0.75 load factor
    if (
        tab->size > (size_t)(tab->len * 0.75F) &&
        tab->len < INT_MAX >> 2
    )
    {
        if (rehash(tab)) index = (hash & INT_MAX) % tab->len;
        else return NULL; // rehash failure
    }

    // add
    entry = malloc(sizeof(HashEntry));
    if (entry == NULL) return NULL;

    entry->hash = hash;
    entry->key = key;
    entry->value = value;

    add_entry(tab, entry, index);

    return NULL;
}

void *hst_get(Hashtable *tab, void *key)
{
    int hash = tab->hc(key);
    size_t index = (hash & INT_MAX) % tab->len;

    HashEntry *entry = find(tab, hash, key, index);
    if (entry != NULL) return entry->value;

    return NULL;
}

void *hst_remove(Hashtable *tab, void *key)
{
    int hash = tab->hc(key);
    size_t index = (hash & INT_MAX) % tab->len;

    for (
        HashEntry *prev = NULL, *e = tab->table[index];
        e != NULL;
        prev = e, e = e->next
    )
    {
        if (hash == e->hash && tab->eq(key, e->key))
        {
            void *value = e->value;
            tab->size--;

            if (prev == NULL)
                tab->table[index] = e->next;
            else
                prev->next = e->next;

            free(e);

            return value;
        }
    }

    return NULL;
}

bool hst_contains_key(Hashtable *tab, void *key)
{
    int hash = tab->hc(key);
    size_t index = (hash & INT_MAX) % tab->len;

    return find(tab, hash, key, index) != NULL;
}

HashEntry *hst_iter_first(Hashtable *tab)
{
    size_t len = tab->len;
    HashEntry **table = tab->table;

    size_t i = 0;
    HashEntry *e = NULL;

    for (; i < len && (e = table[i]) == NULL; ++i);

    tab->iter_index = i;
    tab->iter_entry = e;

    return e;
}

HashEntry *hst_iter_next(Hashtable *tab)
{
    HashEntry *e = tab->iter_entry;
    if (e == NULL) return NULL;

    e = e->next;
    if (e == NULL)
    {
        size_t len = tab->len;
        HashEntry **table = tab->table;

        size_t i = tab->iter_index + 1;

        for (; i < len && (e = table[i]) == NULL; ++i);

        tab->iter_index = i;
    }

    tab->iter_entry = e;

    return e;
}

void hst_for_each(Hashtable *tab, void (*action)(void *, void *))
{
    size_t len = tab->len;
    HashEntry **table = tab->table;

    for (size_t i = 0; i < len; ++i)
        for (HashEntry *e = table[i]; e != NULL; e = e->next)
            action(e->key, e->value);
}

size_t hst_size(Hashtable *tab)
{
    return tab->size;
}

bool hst_is_empty(Hashtable *tab)
{
    return tab->size == 0;
}

void hst_clear(Hashtable *tab)
{
    size_t len = tab->len;
    HashEntry **table = tab->table;

    for (size_t i = 0; i < len; ++i)
    {
        for (HashEntry *e = table[i]; e != NULL;)
        {
            HashEntry *curr = e;
            e = e->next;

            free(curr);
        }

        table[i] = NULL;
    }

    tab->size = 0;
}

void hst_free(Hashtable **tab)
{
    if (*tab == NULL) return;

    hst_clear(*tab);

    free((*tab)->table);
    free(*tab);

    *tab = NULL;
}

void *hse_get_key(HashEntry *entry)
{
    return entry->key;
}

void *hse_get_value(HashEntry *entry)
{
    return entry->value;
}

void *hse_set_value(HashEntry *entry, void *value)
{
    void *old_value = entry->value;
    entry->value = value;

    return old_value;
}



static bool init(Hashtable *tab, size_t len)
{
    HashEntry **table = malloc(len * sizeof(HashEntry *));
    if (table == NULL) return false;

    for (size_t i = 0; i < len; ++i) table[i] = NULL;

    tab->table = table;
    tab->len = len;
    tab->size = 0;

    return true;
}

static HashEntry *find(Hashtable *tab, int hash, void *key, size_t index)
{
    for (HashEntry *e = tab->table[index]; e != NULL; e = e->next)
        if (hash == e->hash && tab->eq(key, e->key))
            return e;

    return NULL;
}

static bool rehash(Hashtable *tab)
{
    size_t len = tab->len;
    HashEntry **table = tab->table;

    size_t new_len = (len << 1) + 1;
    if (!init(tab, new_len)) return false;

    for (size_t i = 0; i < len; ++i)
    {
        for (HashEntry *e = table[i]; e != NULL;)
        {
            HashEntry *curr = e;
            e = e->next;

            add_entry(tab, curr, (curr->hash & INT_MAX) % new_len);
        }
    }

    free(table);

    return true;
}

static void add_entry(Hashtable *tab, HashEntry *entry, size_t index)
{
    entry->next = tab->table[index];
    tab->table[index] = entry;
    tab->size++;
}