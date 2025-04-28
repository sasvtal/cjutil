#include "table.h"

#include <stdlib.h>

/*
    init data table
*/
static bool init_table(Table *tab, int len);

/*
    get an entry by hash, key, and index
*/
static Entry *get_entry(Table *tab, int hash, void *key, int index);

/*
    grow data table and refresh entry index
*/
static bool refresh_table(Table *tab);

/*
    add an entry
*/
static void add_entry(Table *tab, Entry *entry, int index);



Table *tb_new(hash_code hc, equals eq)
{
    Table *tab = (Table *)malloc(sizeof(Table));
    if (tab == NULL) return NULL;

    if (!init_table(tab, 10))
    {
        free(tab);
        return NULL;
    }

    tab->hc = hc;
    tab->eq = eq;

    return tab;
}

bool tb_put(Table *tab, void *key, void *value)
{
    int hash = tab->hc(key);
    int index = hash % tab->len;

    // set
    Entry *entry = get_entry(tab, hash, key, index);
    if (entry != NULL)
    {
        entry->value = value;
        return true;
    }

    // add
    if (tab->count == tab->len)
    {
        if (refresh_table(tab)) index = hash % tab->len;
        else return false; // refresh failure
    }

    entry = (Entry *)malloc(sizeof(Entry));
    if (entry == NULL) return false;

    entry->hash = hash;
    entry->key = key;
    entry->value = value;

    add_entry(tab, entry, index);

    return true;
}

void *tb_get(Table *tab, void *key)
{
    int hash = tab->hc(key);
    int index = hash % tab->len;

    Entry *entry = get_entry(tab, hash, key, index);
    if (entry != NULL) return entry->value;

    return NULL;
}

void *tb_remove(Table *tab, void *key)
{
    int hash = tab->hc(key);
    int index = hash % tab->len;

    for (
        Entry *prev = NULL, *e = tab->table[index];
        e != NULL;
        prev = e, e = e->next
    )
    {
        if (hash == e->hash && tab->eq(key, e->key))
        {
            // equal!
            void *rem_val = e->value;
            tab->size--;

            if (prev == NULL)
            {
                tab->table[index] = e->next;
                if (e->next == NULL) tab->count--;
            }
            else prev->next = e->next;

            free(e);
            return rem_val;
        }
    }

    return NULL;
}

void **tb_to_array(Table *tab, bool get_key)
{
    void **arr = (void **)malloc(tab->size * sizeof(void *));
    if (arr == NULL) return NULL;

    int len = tab->len;
    Entry **table = tab->table;

    int index = 0;
    if (get_key)
    {
        for (int i = 0; i < len; i++)
            for (Entry *e = table[i]; e != NULL; e = e->next)
                arr[index++] = e->key;
    }
    else
    {
        for (int i = 0; i < len; i++)
            for (Entry *e = table[i]; e != NULL; e = e->next)
                arr[index++] = e->value;
    }

    return arr;
}

bool tb_contains_key(Table *tab, void *key)
{
    int hash = tab->hc(key);
    int index = hash % tab->len;

    return get_entry(tab, hash, key, index) != NULL;
}

void tb_for_each(Table *tab, void (*action)(void *, void *))
{
    int len = tab->len;
    Entry **table = tab->table;

    for (int i = 0; i < len; i++)
        for (Entry *e = table[i]; e != NULL; e = e->next)
            action(e->key, e->value);
}

int tb_size(Table *tab)
{
    return tab->size;
}

bool tb_is_empty(Table *tab)
{
    return tab->size == 0;
}

void tb_clear(Table *tab)
{
    int len = tab->len;
    Entry **table = tab->table;

    for (int i = 0; i < len; i++)
    {
        for (Entry *e = table[i]; e != NULL;)
        {
            Entry *curr = e;
            e = e->next;
            free(curr);
        }

        table[i] = NULL;
    }

    tab->count = 0;
    tab->size = 0;
}

void tb_free(Table **tab)
{
    if (*tab == NULL) return;

    tb_clear(*tab);

    free((*tab)->table);
    free(*tab);

    *tab = NULL;
}



static bool init_table(Table *tab, int len)
{
    Entry **table = (Entry **)malloc(len * sizeof(Entry *));
    if (table == NULL) return false;

    for (int i = 0; i < len; i++) table[i] = NULL;

    tab->table = table;
    tab->len = len;
    tab->count = 0;
    tab->size = 0;

    return true;
}

static Entry *get_entry(Table *tab, int hash, void *key, int index)
{
    for (Entry *e = tab->table[index]; e != NULL; e = e->next)
        if (hash == e->hash && tab->eq(key, e->key))
            // equal!
            return e;

    return NULL;
}

static bool refresh_table(Table *tab)
{
    int len = tab->len;
    Entry **table = tab->table;

    int new_len = len << 1;
    if (!init_table(tab, new_len)) return false;

    for (int i = 0; i < len; i++)
    {
        for (Entry *e = table[i]; e != NULL;)
        {
            Entry *curr = e;
            e = e->next;
            curr->next = NULL; // break linked list
            add_entry(tab, curr, curr->hash % new_len);
        }
    }

    free(table);

    return true;
}

static void add_entry(Table *tab, Entry *entry, int index)
{
    Entry *e = tab->table[index];
    if (e == NULL) tab->count++;
    entry->next = e;

    tab->table[index] = entry;
    tab->size++;
}