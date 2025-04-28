/*
    hash table
*/
#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>

typedef int (*hash_code)(void *);

typedef bool (*equals)(void *, void *);

typedef struct e
{
    int hash;
    void *key;
    void *value;
    struct e *next;
}
Entry;

typedef struct
{
    Entry **table;
    hash_code hc;
    equals eq;
    int len;
    int count;
    int size;
}
Table;

/*
    create a table
    hc: calculate the hash code for the key
    eq: check if the keys are equal
*/
Table *tb_new(hash_code hc, equals eq);

/*
    put an entry
    if the key exists
    overwrite the value
*/
bool tb_put(Table *tab, void *key, void *value);

/*
    get an entry value by key
*/
void *tb_get(Table *tab, void *key);

/*
    remove an entry by key
*/
void *tb_remove(Table *tab, void *key);

/*
    get all keys or values as array
*/
void **tb_to_array(Table *tab, bool get_key);

/*
    check if the table contains the specified key
*/
bool tb_contains_key(Table *tab, void *key);

/*
    traverse the table
*/
void tb_for_each(Table *tab, void (*action)(void *, void *));

/*
    get the size of the table
*/
int tb_size(Table *tab);

/*
    check if the table is empty
*/
bool tb_is_empty(Table *tab);

/*
    clear the table
*/
void tb_clear(Table *tab);

/*
    free the table
*/
void tb_free(Table **tab);

#endif // !TABLE_H