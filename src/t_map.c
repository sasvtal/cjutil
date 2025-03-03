#include "t_map.h"

/**
* recursion
* get a node by key
*/
static Node *get_node(void *key, Node *root, compare cmp);

/**
* recursion
* add a node
*/
static void add_node(Node *node, TMap *map, Node *root);

/**
* fix imbalance caused by adding a node
* find the imbalanced node and fix it
*/
static void fix_add(Node *start, TMap *map);

/**
* check if the node is the left child of the parent
*/
static bool is_left(Node *node);

/**
* check if the node needs to rotate
* if it needs to be rotated, then rotate it
*/
static bool rotate(Node *node, TMap *map);

/**
* left rotate the node
*/
static void left_rotate(Node *node, TMap *map);

/**
* right rotate the node
*/
static void right_rotate(Node *node, TMap *map);

/**
* recursion
* remove a node
*/
static void remove_node(Node *node, TMap *map);

/**
* fix imbalance caused by removing a node
* find the imbalanced node and fix it
*/
static void fix_remove(Node *start, TMap *map);

/**
* recursion
* get all keys
*/
static void keys(void **arr, Node *root, size_t *index);

/**
* recursion
* get all values
*/
static void values(void **arr, Node *root, size_t *index);

/**
* recursion
* action on each node
*/
static void each_node(Node *root, void (*func)(void *, void *));

/**
* recursion
* clear all nodes
*/
static void clear_node(Node *root);



TMap *tm_new(compare cmp)
{
    TMap *map = (TMap *)malloc(sizeof(TMap));
    if (map == NULL) return NULL;

    map->root = NULL;
    map->cmp = cmp;
    map->size = 0;

    return map;
}

bool tm_put(TMap *map, void *key, void *value)
{
    Node *root = map->root;

    // set
    Node *node = get_node(key, root, map->cmp);
    if (node != NULL)
    {
        node->value = value;
        return true;
    }

    // add
    node = (Node *)malloc(sizeof(Node));
    if (node == NULL) return false;

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->state = 0;
    node->key = key;
    node->value = value;

    if (root == NULL) map->root = node;
    else add_node(node, map, root);

    map->size++;

    return true;
}

void *tm_get(TMap *map, void *key)
{
    Node *node = get_node(key, map->root, map->cmp);
    if (node == NULL) return NULL;

    return node->value;
}

void *tm_remove(TMap *map, void *key)
{
    Node *node = get_node(key, map->root, map->cmp);
    if (node == NULL) return NULL;

    void *rem_val = node->value;

    if (map->size == 1)
    {
        free(node);
        map->root = NULL;
    }
    else remove_node(node, map);

    map->size--;

    return rem_val;
}

void **tm_kvs(TMap *map, bool key)
{
    void **kvs = (void **)malloc(map->size * sizeof(void *));
    if (kvs == NULL) return NULL;

    size_t index = 0;

    if (key) keys(kvs, map->root, &index);
    else values(kvs, map->root, &index);

    return kvs;
}

bool tm_contk(TMap *map, void *key)
{
    return get_node(key, map->root, map->cmp) != NULL;
}

void tm_each(TMap *map, void (*func)(void *, void *))
{
    each_node(map->root, func);
}

size_t tm_size(TMap *map)
{
    return map->size;
}

bool tm_empty(TMap *map)
{
    return map->size == 0;
}

void tm_clear(TMap *map)
{
    clear_node(map->root);

    map->root = NULL;
    map->size = 0;
}

void tm_free(TMap **map)
{
    if (*map == NULL) return;

    tm_clear(*map);

    free(*map);

    *map = NULL;
}



static Node *get_node(void *key, Node *root, compare cmp)
{
    if (root == NULL) return NULL;

    int r = cmp(key, root->key);

    if (r == 0)
        return root;
    else if (r < 0)
        // node in the left subtree
        return get_node(key, root->left, cmp);
    else
        // node in the right subtree
        return get_node(key, root->right, cmp);
}

static void add_node(Node *node, TMap *map, Node *root)
{
    if (map->cmp(node->key, root->key) < 0)
    {
        if (root->left == NULL)
        {
            root->left = node;
            node->parent = root;
            root->state--;

            if (root->right == NULL) fix_add(root, map);
        }
        else add_node(node, map, root->left);
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = node;
            node->parent = root;
            root->state++;

            if (root->left == NULL) fix_add(root, map);
        }
        else add_node(node, map, root->right);
    }
}

static void fix_add(Node *start, TMap *map)
{
    for (Node *p, *n = start; (p = n->parent) != NULL;)
    {
        if (is_left(n)) p->state--;
        else p->state++;

        if (rotate(p, map)) break;

        n = p;
    }
}

static bool is_left(Node *node)
{
    return node->parent->left == node;
}

static bool rotate(Node *node, TMap *map)
{
    if (node->state == 2)
    {
        for (Node *n = node; n != NULL; n = n->right)
            if (n->state == -1) right_rotate(n, map);

        left_rotate(node, map);

        return true;
    }
    else if (node->state == -2)
    {
        for (Node *n = node; n != NULL; n = n->left)
            if (n->state == 1) left_rotate(n, map);

        right_rotate(node, map);

        return true;
    }

    return false;
}

static void left_rotate(Node *node, TMap *map)
{
    node->state = 0;

    Node *right = node->right;
    right->state = 0;

    Node *parent = node->parent;

    node->right = right->left;
    if (right->left != NULL) right->left->parent = node;

    right->left = node;
    right->parent = parent;

    if (parent != NULL)
    {
        if (is_left(node)) parent->left = right;
        else parent->right = right;
    }
    else map->root = right;

    node->parent = right;
}

static void right_rotate(Node *node, TMap *map)
{
    node->state = 0;

    Node *left = node->left;
    left->state = 0;

    Node *parent = node->parent;

    node->left = left->right;
    if (left->right != NULL) left->right->parent = node;

    left->right = node;
    left->parent = parent;

    if (parent != NULL)
    {
        if (is_left(node)) parent->left = left;
        else parent->right = left;
    }
    else map->root = left;

    node->parent = left;
}

static void remove_node(Node *node, TMap *map)
{
    if (node->left == NULL && node->right == NULL)
    {
        Node *parent = node->parent;

        if (is_left(node)) parent->left = NULL;
        else parent->right = NULL;

        fix_remove(node, map);
        free(node);
    }
    else if (node->left != NULL && node->right == NULL)
    {
        Node *left = node->left;

        node->parent->left = left;
        left->parent = node->parent;

        fix_remove(left, map);
        free(node);
    }
    else if (node->left == NULL && node->right != NULL)
    {
        Node *right = node->right;

        node->parent->right = right;
        right->parent = node->parent;

        fix_remove(right, map);
        free(node);
    }
    else
    {
        Node *left_max = node->left;
        for (; left_max->right != NULL; left_max = left_max->right);

        node->key = left_max->key;
        node->value = left_max->value;

        remove_node(left_max, map);
    }
}

static void fix_remove(Node *start, TMap *map)
{
    for (Node *p, *n = start; (p = n->parent) != NULL;)
    {
        if (is_left(n)) p->state++;
        else p->state--;

        if (rotate(p, map)) break;

        n = p;
    }
}

static void keys(void **arr, Node *root, size_t *index)
{
    if (root->left != NULL) keys(arr, root->left, index);

    arr[*index] = root->key;
    *index = *index + 1;

    if (root->right != NULL) keys(arr, root->right, index);
}

static void values(void **arr, Node *root, size_t *index)
{
    if (root->left != NULL) values(arr, root->left, index);

    arr[*index] = root->value;
    *index = *index + 1;

    if (root->right != NULL) values(arr, root->right, index);
}

static void each_node(Node *root, void (*func)(void *, void *))
{
    if (root->left != NULL) each_node(root->left, func);

    func(root->key, root->value);

    if (root->right != NULL) each_node(root->right, func);
}

static void clear_node(Node *root)
{
    if (root->left != NULL) clear_node(root->left);

    if (root->right != NULL) clear_node(root->right);

    free(root);
}