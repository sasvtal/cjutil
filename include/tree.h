/*
    binary tree
*/
#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef int (*compare)(void *, void *);

typedef struct n
{
    struct n *parent;
    struct n *left;
    struct n *right;
    int status;
    void *key;
    void *value;
}
Node;

typedef struct
{
    Node *root;
    compare cmp;
    int size;
}
Tree;

/*
    create a tree
    cmp: compare keys
         k1 < k2 return int < 0
         k1 = k2 return 0
         k1 > k2 return int > 0
*/
Tree *tr_new(compare cmp);

/*
    put an entry
    if the key exists
    overwrite the value
*/
bool tr_put(Tree *tree, void *key, void *value);

/*
    get an entry value by key
*/
void *tr_get(Tree *tree, void *key);

/*
    remove an entry by key
*/
void *tr_remove(Tree *tree, void *key);

/*
    get all keys or values as array
*/
void **tr_to_array(Tree *tree, bool get_key);

/*
    check if the tree contains the specified key
*/
bool tr_contains_key(Tree *tree, void *key);

/*
    traverse the tree
*/
void tr_for_each(Tree *tree, void (*action)(void *, void *));

/*
    get the size of the tree
*/
int tr_size(Tree *tree);

/*
    check if the tree is empty
*/
bool tr_is_empty(Tree *tree);

/*
    clear the tree
*/
void tr_clear(Tree *tree);

/*
    free the tree
*/
void tr_free(Tree **tree);

#endif // !TREE_H