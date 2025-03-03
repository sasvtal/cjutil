/*
    hash map

    v1.0
*/
#ifndef H_MAP_H
#define H_MAP_H

#include <stdlib.h>
#include <stdbool.h>

typedef size_t (*hash_code)(void *);

typedef bool (*equals)(void *, void *);

typedef struct e
{
    size_t hash;
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
    size_t len;
    size_t count;
    size_t size;
}
HMap;

/**
* create hash map
* 
* Parameters:
* - hc: calculate the hash code for the key
* - eq: compare whether the keys are equal
* 
* Returns:
* - hash map
*/
HMap *hm_new(hash_code hc, equals eq);

/**
* put an entry
* if the key exists, overwrite the value
* 
* Parameters:
* - map: hash map
* - key: entry key
* - value: entry value
* 
* Returns:
* - success or failure
*/
bool hm_put(HMap *map, void *key, void *value);

/**
* get an entry value by key
* 
* Parameters:
* - map: hash map
* - key: entry key
* 
* Returns:
* - entry value
*/
void *hm_get(HMap *map, void *key);

/**
* remove an entry by key
* 
* Parameters:
* - map: hash map
* - key: entry key
* 
* Returns:
* - removed entry value
*/
void *hm_remove(HMap *map, void *key);

/**
* get all keys or values
* 
* Parameters:
* - map: hash map
* - key: get key
* 
* Returns:
* - keys or values
*/
void **hm_kvs(HMap *map, bool key);

/**
* check if the hash map contains the specified key
* 
* Parameters:
* - map: hash map
* - key: entry key
* 
* Returns:
* - yes or no
*/
bool hm_contk(HMap *map, void *key);

/**
* traverse hash map
* 
* Parameters:
* - map: hash map
* - func: action on each key and value
*/
void hm_each(HMap *map, void (*func)(void *, void *));

/**
* get the size of the hash map
* 
* Parameters:
* - map: hash map
* 
* Returns:
* - size
*/
size_t hm_size(HMap *map);

/**
* check if the hash map is empty
* 
* Parameters:
* - map: hash map
* 
* Returns:
* - yes or no
*/
bool hm_empty(HMap *map);

/**
* clear hash map
* 
* Parameters:
* - map: hash map
*/
void hm_clear(HMap *map);

/**
* free hash map
* 
* Parameters:
* - map: hash map address
*/
void hm_free(HMap **map);

/**
* callback
* calculate the hash code for a string key
* 
* Parameters:
* - key: string key
* 
* Returns:
* - hash code
*/
size_t hm_hcs(void *key);

#endif // !H_MAP_H