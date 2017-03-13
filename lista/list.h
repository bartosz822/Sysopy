#ifndef LISTA_LIBRARY_H
#define LISTA_LIBRARY_H

#include "person.h"
#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Person *data;
    struct Node *next;
    struct Node *prev;
} Node;

struct List {
    int len;
    struct Node *first;
    struct Node *last;
} List;

struct List *init();

void delete_list(struct List *list);

void delete_node_from_list(struct List *list, struct Node *node);

void insert_to_beggining_list(struct List *list, struct Node *newNode);

void insert_to_end_list(struct List *list, struct Node *newNode);

void print_forwards(struct List *list);

void print_backwards(struct List *list);

void sort_by_first_name(struct List *list);

void sort_by_last_name(struct List *list);

void sort_by_email(struct List *list);

void sort_by_phone(struct List *list);

void sort_by_adress(struct List *list);

void sort_by_birth(struct List *list);

struct Node *create_node(struct Person *person);

void delete_person(struct List *list, char *first_name, char *last_name);

struct Person *find_person(struct List *list, char *first_name, char *last_name);

#endif