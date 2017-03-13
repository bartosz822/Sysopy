//
// Created by bartek on 09.03.17.
//
#include <string.h>
#include "tree.h"

struct Tree *init_tree() {
    struct Tree *new = (struct Tree *) malloc(sizeof(struct Tree));
    new->root = NULL;
    new->comparator = &first_name_comparator;
    return new;
}

struct Tree_node *create_tree_node(struct Person *person) {
    struct Tree_node *new = (struct Tree_node *) malloc(sizeof(struct Tree_node));
    new->data = person;
    new->left = NULL;
    new->right = NULL;
    return new;
}

struct Tree_node *
insert_node(struct Tree_node *root, struct Tree_node *new, int comparator(struct Person *p1, struct Person *p2)) {
    if (root == NULL) {
        return new;
    } else if (comparator(root->data, new->data) > 0) {
        root->left = insert_node(root->left, new, comparator);
        return root;
    } else {
        root->right = insert_node(root->right, new, comparator);
        return root;
    }
}

void insert(struct Tree *tree, struct Tree_node *node) {
    tree->root = insert_node(tree->root, node, tree->comparator);
}

void print_node(struct Tree_node *node) {
    if (node == NULL) return;
    print_node(node->left);
    print_person(node->data);
    print_node(node->right);
}

void print_tree(struct Tree *tree) {
    if (tree == NULL) return;
    print_node(tree->root);
    printf("\n");
};

void insert_recursive_from_node(struct Tree *tree, struct Tree_node *node) {
    if (node == NULL) return;
    else if (node->left == NULL && node->right == NULL) {
        insert(tree, node);
    } else {
        insert_recursive_from_node(tree, node->left);
        struct Tree_node *right = node->right;
        node->left = NULL;
        node->right = NULL;
        insert_recursive_from_node(tree, node);
        insert_recursive_from_node(tree, right);
    }
}

void rebuild_tree(struct Tree *tree, int comparator(struct Person *, struct Person *)) {
    if (tree->comparator == comparator) return;
    struct Tree *tmp = init_tree();
    tmp->comparator = comparator;
    insert_recursive_from_node(tmp, tree->root);
    tree->root = tmp->root;
    tree->comparator = comparator;
    free(tmp);
}

struct Tree_node **find_node_recursive(struct Tree_node **node, char *first_name, char *last_name) {
    if (node == NULL || (*node) == NULL) return NULL;
    if (strcmp((*node)->data->first_name, first_name) == 0 && strcmp((*node)->data->last_name, last_name) == 0)
        return node;
    struct Tree_node **tmp = find_node_recursive(&(*node)->left, first_name, last_name);
    if (tmp != NULL) return tmp;
    tmp = find_node_recursive(&(*node)->right, first_name, last_name);
    return tmp;
}


struct Tree_node **find_node_ptr(struct Tree *tree, char *first_name, char *last_name) {
    return find_node_recursive(&tree->root, first_name, last_name);
}

struct Person *find_person_tree(struct Tree *tree, char *first_name, char *last_name) {
    struct Tree_node **p = find_node_ptr(tree, first_name, last_name);
    if (p == NULL) return NULL;
    else return (*p)->data;
}


void delete_node(struct Tree *tree, struct Tree_node **node) {
    if ((*node)->left == NULL && (*node)->right == NULL) {
        kill_person((*node)->data);
        free(*node);
        (*node) = NULL;
    } else if ((*node)->left == NULL) {
        kill_person((*node)->data);
        struct Tree_node *tmp = (*node)->right;
        free(*node);
        *node = tmp;
    } else if ((*node)->right == NULL) {
        kill_person((*node)->data);
        struct Tree_node *tmp = (*node)->left;
        free(*node);
        *node = tmp;
    } else {
        kill_person((*node)->data);
        struct Tree_node *left = (*node)->left;
        struct Tree_node *right = (*node)->right;
        free(*node);
        *node = left;
        insert(tree, right);
    }
}

void delete_person_tree(struct Tree *tree, char *first_name, char *last_name) {
    if (tree == NULL) return;
    struct Tree_node **ptr = find_node_recursive(&tree->root, first_name, last_name);
    if (ptr == NULL) return;
    delete_node(tree, ptr);
}

void delete_recursive(struct Tree_node *node) {
    if (node == NULL) return;
    else if (node->left == NULL && node->right == NULL) {
        kill_person(node->data);
        free(node);
    } else {
        delete_recursive(node->left);
        delete_recursive(node->right);
        kill_person(node->data);
        free(node);

    }
}


void delete_tree(struct Tree *tree) {
    delete_recursive(tree->root);
    free(tree);
}



