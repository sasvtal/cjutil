#include "tree.h"

#include <stdlib.h>

/*
    recursion
    get a node by key
*/
static Node *get_node(void *key, Node *root, compare cmp);

/*
    recursion
    add a node
*/
static void add_node(Node *node, Tree *tree, Node *root);

/*
    fix imbalance caused by adding a node
    find the imbalanced node and fix it
*/
static void fix_add(Node *start, Tree *tree);

/*
    check if the node is the left child of the parent
*/
static bool is_left_child(Node *node);

/*
    check if the node needs to rotate
    if it needs to be rotated
    then rotate it
*/
static bool rotate_node(Node *node, Tree *tree);

/*
    left rotate the node
*/
static void left_rotate(Node *node, Tree *tree);

/*
    right rotate the node
*/
static void right_rotate(Node *node, Tree *tree);

/*
    recursion
    remove a node
*/
static void remove_node(Node *node, Tree *tree);

/*
    fix imbalance caused by removing a node
    find the imbalanced node and fix it
*/
static void fix_remove(Node *start, Tree *tree);

/*
    recursion
    add all keys to the array
*/
static void key_array(void **arr, Node *root, int *index);

/*
    recursion
    add all values to the array
*/
static void value_array(void **arr, Node *root, int *index);

/*
    recursion
    traverse each node
*/
static void for_each(Node *root, void (*action)(void *, void *));

/*
    recursion
    clear all nodes
*/
static void clear_node(Node *root);



Tree *tr_new(compare cmp)
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    tree->cmp = cmp;
    tree->size = 0;

    return tree;
}

bool tr_put(Tree *tree, void *key, void *value)
{
    Node *root = tree->root;

    // set
    Node *node = get_node(key, root, tree->cmp);
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
    node->status = 0;
    node->key = key;
    node->value = value;

    if (root == NULL) tree->root = node;
    else add_node(node, tree, root);

    tree->size++;

    return true;
}

void *tr_get(Tree *tree, void *key)
{
    Node *node = get_node(key, tree->root, tree->cmp);
    if (node == NULL) return NULL;

    return node->value;
}

void *tr_remove(Tree *tree, void *key)
{
    Node *node = get_node(key, tree->root, tree->cmp);
    if (node == NULL) return NULL;

    void *rem_val = node->value;

    if (tree->size == 1)
    {
        free(node);
        tree->root = NULL;
    }
    else remove_node(node, tree);

    tree->size--;

    return rem_val;
}

void **tr_to_array(Tree *tree, bool get_key)
{
    void **arr = (void **)malloc(tree->size * sizeof(void *));
    if (arr == NULL) return NULL;

    int index = 0;

    if (get_key) key_array(arr, tree->root, &index);
    else value_array(arr, tree->root, &index);

    return arr;
}

bool tr_contains_key(Tree *tree, void *key)
{
    return get_node(key, tree->root, tree->cmp) != NULL;
}

void tr_for_each(Tree *tree, void (*action)(void *, void *))
{
    for_each(tree->root, action);
}

int tr_size(Tree *tree)
{
    return tree->size;
}

bool tr_is_empty(Tree *tree)
{
    return tree->size == 0;
}

void tr_clear(Tree *tree)
{
    clear_node(tree->root);

    tree->root = NULL;
    tree->size = 0;
}

void tr_free(Tree **tree)
{
    if (*tree == NULL) return;

    tr_clear(*tree);

    free(*tree);

    *tree = NULL;
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

static void add_node(Node *node, Tree *tree, Node *root)
{
    if (tree->cmp(node->key, root->key) < 0)
    {
        if (root->left == NULL)
        {
            root->left = node;
            node->parent = root;
            root->status--;

            if (root->right == NULL) fix_add(root, tree);
        }
        else add_node(node, tree, root->left);
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = node;
            node->parent = root;
            root->status++;

            if (root->left == NULL) fix_add(root, tree);
        }
        else add_node(node, tree, root->right);
    }
}

static void fix_add(Node *start, Tree *tree)
{
    for (Node *p, *n = start; (p = n->parent) != NULL; n = p)
    {
        if (is_left_child(n)) p->status--;
        else p->status++;

        if (rotate_node(p, tree)) break;
    }
}

static bool is_left_child(Node *node)
{
    return node->parent->left == node;
}

static bool rotate_node(Node *node, Tree *tree)
{
    if (node->status == 2)
    {
        for (Node *n = node; n != NULL; n = n->right)
            if (n->status == -1) right_rotate(n, tree);

        left_rotate(node, tree);

        return true;
    }
    else if (node->status == -2)
    {
        for (Node *n = node; n != NULL; n = n->left)
            if (n->status == 1) left_rotate(n, tree);

        right_rotate(node, tree);

        return true;
    }

    return false;
}

static void left_rotate(Node *node, Tree *tree)
{
    node->status = 0;

    Node *right = node->right;
    right->status = 0;

    Node *parent = node->parent;

    node->right = right->left;
    if (right->left != NULL) right->left->parent = node;

    right->left = node;
    right->parent = parent;

    if (parent != NULL)
    {
        if (is_left_child(node)) parent->left = right;
        else parent->right = right;
    }
    else tree->root = right;

    node->parent = right;
}

static void right_rotate(Node *node, Tree *tree)
{
    node->status = 0;

    Node *left = node->left;
    left->status = 0;

    Node *parent = node->parent;

    node->left = left->right;
    if (left->right != NULL) left->right->parent = node;

    left->right = node;
    left->parent = parent;

    if (parent != NULL)
    {
        if (is_left_child(node)) parent->left = left;
        else parent->right = left;
    }
    else tree->root = left;

    node->parent = left;
}

static void remove_node(Node *node, Tree *tree)
{
    if (node->left == NULL && node->right == NULL)
    {
        Node *parent = node->parent;

        if (is_left_child(node)) parent->left = NULL;
        else parent->right = NULL;

        fix_remove(node, tree);
        free(node);
    }
    else if (node->left != NULL && node->right == NULL)
    {
        Node *left = node->left;

        node->parent->left = left;
        left->parent = node->parent;

        fix_remove(left, tree);
        free(node);
    }
    else if (node->left == NULL && node->right != NULL)
    {
        Node *right = node->right;

        node->parent->right = right;
        right->parent = node->parent;

        fix_remove(right, tree);
        free(node);
    }
    else
    {
        Node *left_max = node->left;
        for (; left_max->right != NULL; left_max = left_max->right);

        node->key = left_max->key;
        node->value = left_max->value;

        remove_node(left_max, tree);
    }
}

static void fix_remove(Node *start, Tree *tree)
{
    for (Node *p, *n = start; (p = n->parent) != NULL; n = p)
    {
        if (is_left_child(n)) p->status++;
        else p->status--;

        if (rotate_node(p, tree)) break;
    }
}

static void key_array(void **arr, Node *root, int *index)
{
    if (root->left != NULL) key_array(arr, root->left, index);

    arr[*index] = root->key;
    *index = *index + 1;

    if (root->right != NULL) key_array(arr, root->right, index);
}

static void value_array(void **arr, Node *root, int *index)
{
    if (root->left != NULL) value_array(arr, root->left, index);

    arr[*index] = root->value;
    *index = *index + 1;

    if (root->right != NULL) value_array(arr, root->right, index);
}

static void for_each(Node *root, void (*action)(void *, void *))
{
    if (root->left != NULL) for_each(root->left, action);

    action(root->key, root->value);

    if (root->right != NULL) for_each(root->right, action);
}

static void clear_node(Node *root)
{
    if (root->left != NULL) clear_node(root->left);

    if (root->right != NULL) clear_node(root->right);

    free(root);
}