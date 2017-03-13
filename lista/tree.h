//
// Created by bartek on 09.03.17.
//

#ifndef LISTA_TREE_H
#define LISTA_TREE_H

#include "person.h"
#include <stdlib.h>

struct Tree_node {
    struct Person *data;
    struct Tree_node *left;
    struct Tree_node *right;
} Tree_node;

struct Tree {
    struct Tree_node *root;

    int (*comparator)(struct Person *, struct Person *);
} Tree;

struct Tree *init_tree();

void delete_tree(struct Tree *);

struct Tree_node *create_tree_node(struct Person *person);

void insert(struct Tree *tree, struct Tree_node *node);

void print_tree(struct Tree *tree);

void rebuild_tree(struct Tree *tree, int comparator(struct Person *p1, struct Person *p2));

struct Person *find_person_tree(struct Tree *tree, char *first_name, char *last_name);

void delete_person_tree(struct Tree *tree, char *first_name, char *last_name);


#endif //LISTA_TREE_H

