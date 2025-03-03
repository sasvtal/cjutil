/*
    tree map

    v1.0
*/
#ifndef T_MAP_H
#define T_MAP_H

#include <stdlib.h>
#include <stdbool.h>

typedef int (*compare)(void *, void *);

typedef struct n
{
    struct n *parent;
    struct n *left;
    struct n *right;
    int state;
    void *key;
    void *value;
}
Node;

typedef struct
{
    Node *root;
    compare cmp;
    size_t size;
}
TMap;

/**
* create tree map
* 
* Parameters:
* - cmp: compare keys
*        k1 < k2 rtn n < 0
*        k1 = k2 rtn 0
*        k1 > k2 rtn n > 0
* 
* Returns:
* - tree map
*/
TMap *tm_new(compare cmp);

/**
* put an entry
* if the key exists, overwrite the value
* 
* Parameters:
* - map: tree map
* - key: entry key
* - value: entry value
* 
* Returns:
* - success or failure
*/
bool tm_put(TMap *map, void *key, void *value);

/**
* get an entry value by key
* 
* Parameters:
* - map: tree map
* - key: entry key
* 
* Returns:
* - entry value
*/
void *tm_get(TMap *map, void *key);

/**
* remove an entry by key
* 
* Parameters:
* - map: tree map
* - key: entry key
* 
* Returns:
* - removed entry value
*/
void *tm_remove(TMap *map, void *key);

/**
* get all keys or values
* 
* Parameters:
* - map: tree map
* - key: get key
* 
* Returns:
* - keys or values
*/
void **tm_kvs(TMap *map, bool key);

/**
* check if the tree map contains the specified key
* 
* Parameters:
* - map: tree map
* - key: entry key
* 
* Returns:
* - yes or no
*/
bool tm_contk(TMap *map, void *key);

/**
* traverse tree map
* 
* Parameters:
* - map: tree map
* - func: action on each key and value
*/
void tm_each(TMap *map, void (*func)(void *, void *));

/**
* get the size of the tree map
* 
* Parameters:
* - map: tree map
* 
* Returns:
* - size
*/
size_t tm_size(TMap *map);

/**
* check if the tree map is empty
* 
* Parameters:
* - map: tree map
* 
* Returns:
* - yes or no
*/
bool tm_empty(TMap *map);

/**
* clear tree map
* 
* Parameters:
* - map: tree map
*/
void tm_clear(TMap *map);

/**
* free tree map
* 
* Parameters:
* - map: tree map address
*/
void tm_free(TMap **map);

#endif // !T_MAP_H