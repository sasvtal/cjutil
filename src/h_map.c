#include "h_map.h"

/**
* init data table
*/
static bool init_table(HMap *map, size_t len);

/**
* get an entry by hash, key, and index
*/
static Entry *get_entry(HMap *map, size_t hash, void *key, size_t index);

/**
* grow data table and refresh entry index
*/
static bool ref_table(HMap *map);

/**
* add an entry
*/
static void add_entry(HMap *map, Entry *entry, size_t index);



HMap *hm_new(hash_code hc, equals eq)
{
    HMap *map = (HMap *)malloc(sizeof(HMap));
    if (map == NULL) return NULL;

    if (!init_table(map, 10))
    {
        free(map);
        return NULL;
    }

    map->hc = hc;
    map->eq = eq;

    return map;
}

bool hm_put(HMap *map, void *key, void *value)
{
    size_t hash = map->hc(key);
    size_t index = hash % map->len;

    // set
    Entry *entry = get_entry(map, hash, key, index);
    if (entry != NULL)
    {
        entry->value = value;
        return true;
    }

    // add
    if (map->count == map->len)
    {
        if (ref_table(map)) index = hash % map->len;
        else return false; // refresh failure
    }

    entry = (Entry *)malloc(sizeof(Entry));
    if (entry == NULL) return false;

    entry->hash = hash;
    entry->key = key;
    entry->value = value;

    add_entry(map, entry, index);

    return true;
}

void *hm_get(HMap *map, void *key)
{
    size_t hash = map->hc(key);
    size_t index = hash % map->len;

    Entry *entry = get_entry(map, hash, key, index);
    if (entry != NULL) return entry->value;

    return NULL;
}

void *hm_remove(HMap *map, void *key)
{
    size_t hash = map->hc(key);
    size_t index = hash % map->len;

    for (
        Entry *prev = NULL, *e = map->table[index];
        e != NULL;
        prev = e, e = e->next
    )
    {
        if (hash == e->hash && map->eq(key, e->key))
        {
            // equal!
            void *rem_val = e->value;
            map->size--;

            if (prev == NULL)
            {
                map->table[index] = e->next;
                if (e->next == NULL) map->count--;
            }
            else prev->next = e->next;

            free(e);
            return rem_val;
        }
    }

    return NULL;
}

void **hm_kvs(HMap *map, bool key)
{
    void **kvs = (void **)malloc(map->size * sizeof(void *));
    if (kvs == NULL) return NULL;

    size_t len = map->len;
    Entry **table = map->table;

    size_t index = 0;
    if (key)
    {
        for (size_t i = 0; i < len; i++)
            for (Entry *e = table[i]; e != NULL; e = e->next)
                kvs[index++] = e->key;
    }
    else
    {
        for (size_t i = 0; i < len; i++)
            for (Entry *e = table[i]; e != NULL; e = e->next)
                kvs[index++] = e->value;
    }

    return kvs;
}

bool hm_contk(HMap *map, void *key)
{
    size_t hash = map->hc(key);
    size_t index = hash % map->len;

    return get_entry(map, hash, key, index) != NULL;
}

void hm_each(HMap *map, void (*func)(void *, void *))
{
    size_t len = map->len;
    Entry **table = map->table;

    for (size_t i = 0; i < len; i++)
        for (Entry *e = table[i]; e != NULL; e = e->next)
            func(e->key, e->value);
}

size_t hm_size(HMap *map)
{
    return map->size;
}

bool hm_empty(HMap *map)
{
    return map->size == 0;
}

void hm_clear(HMap *map)
{
    size_t len = map->len;
    Entry **table = map->table;

    for (size_t i = 0; i < len; i++)
    {
        for (Entry *e = table[i]; e != NULL;)
        {
            Entry *curr = e;
            e = e->next;
            free(curr);
        }

        table[i] = NULL;
    }

    map->count = 0;
    map->size = 0;
}

void hm_free(HMap **map)
{
    if (*map == NULL) return;

    hm_clear(*map);

    free((*map)->table);
    free(*map);

    *map = NULL;
}

size_t hm_hcs(void *key)
{
    char *k = (char *)key;
    size_t code = 0;

    size_t index = 0;
    while (true)
    {
        char ch = k[index++];
        if (ch == '\0') break;

        size_t n = (size_t)ch;
        n = (n << index) ^ n;

        code += n;
    }

    return code;
}



static bool init_table(HMap *map, size_t len)
{
    Entry **table = (Entry **)malloc(len * sizeof(Entry *));
    if (table == NULL) return false;

    for (size_t i = 0; i < len; i++) table[i] = NULL;

    map->table = table;
    map->len = len;
    map->count = 0;
    map->size = 0;

    return true;
}

static Entry *get_entry(HMap *map, size_t hash, void *key, size_t index)
{
    for (Entry *e = map->table[index]; e != NULL; e = e->next)
        if (hash == e->hash && map->eq(key, e->key))
            // equal!
            return e;

    return NULL;
}

static bool ref_table(HMap *map)
{
    size_t len = map->len;
    Entry **table = map->table;

    size_t new_len = len << 1;
    if (!init_table(map, new_len)) return false;

    for (size_t i = 0; i < len; i++)
    {
        for (Entry *e = table[i]; e != NULL;)
        {
            Entry *curr = e;
            e = e->next;
            curr->next = NULL; // break linked list
            add_entry(map, curr, curr->hash % new_len);
        }
    }

    free(table);

    return true;
}

static void add_entry(HMap *map, Entry *entry, size_t index)
{
    Entry *e = map->table[index];
    if (e == NULL) map->count++;
    entry->next = e;

    map->table[index] = entry;
    map->size++;
}