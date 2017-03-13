#include <string.h>
#include "list.h"


struct List *init() {
    struct List *new = (struct List *) malloc(sizeof(struct List));
    new->len = 0;
    new->first = NULL;
    new->last = NULL;
    return new;
};

void delete_list(struct List *list) {
    if (list == NULL) return;
    struct Node *p = list->first;
    while (p != NULL) {
        struct Node *tmp = p;
        p = p->next;
        kill_person(tmp->data);
        free(tmp);
    }
    free(list);
}

struct Node *find_node(struct List *list, char *first_name, char *last_name) {
    struct Node *p = list->first;
    while (p != NULL) {
        if (strcmp(p->data->first_name, first_name) == 0 && strcmp(p->data->last_name, last_name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}


struct Person *find_person(struct List *list, char *first_name, char *last_name) {
    struct Node *p = find_node(list, first_name, last_name);
    if (p == NULL) return NULL;
    else return p->data;
}

//TODO check it once again
void unpin(struct List *list, struct Node *node) {
    if (list == NULL || node == NULL) return;
    if (list->len == 1) {
        list->first = NULL;
        list->last = NULL;
        list->len = 0;
        node->next = NULL;
        node->prev = NULL;
    } else if (list->first == node) {
        list->first = node->next;
        list->first->prev = NULL;
        list->len--;
        node->next = NULL;
        node->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        list->last->next = NULL;
        list->len--;
        node->next = NULL;
        node->prev = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = NULL;
        node->prev = NULL;
        list->len--;
    }

}

void delete_node_from_list(struct List *list, struct Node *node) {
    if (list == NULL || node == NULL) return;
    unpin(list, node);
    kill_person(node->data);
    free(node);
}

void delete_person(struct List *list, char *first_name, char *last_name) {
    struct Node *p = find_node(list, first_name, last_name);
    if (p == NULL) return;
    else {
        delete_node_from_list(list, p);
    }
}


struct Node *create_node(struct Person *person) {
    struct Node *newNode = (struct Node *) malloc(sizeof(Node));
    newNode->data = person;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insert_to_beggining_list(struct List *list, struct Node *newNode) {
    if (list == NULL || newNode == NULL) return;
    struct Node *first = list->first;
    newNode->next = first;
    list->first = newNode;
    list->len++;
    if (first != NULL) {
        first->prev = newNode;
    } else {
        list->last = newNode;
    }
}

void insert_to_end_list(struct List *list, struct Node *newNode) {
    if (list == NULL || newNode == NULL) return;

    struct Node *last = list->last;
    newNode->prev = last;
    list->last = newNode;
    list->len++;
    if (last != NULL) {
        last->next = newNode;
    } else {
        list->first = newNode;
    }

}


void insert_to_sorted_list(struct List *list, int comparator(struct Person *, struct Person *), struct Node *node) {
    if (list == NULL || node == NULL) return;
    if (list->len == 0) {
        list->first = node;
        list->last = node;
        list->len++;
    } else {
        struct Node *p = list->first;
        while (p != NULL && comparator(p->data, node->data) < 0) {
            p = p->next;
        }
        if (p == list->first) {
            insert_to_beggining_list(list, node);
        } else if (p == NULL) {
            insert_to_end_list(list, node);
        } else {
            p = p->prev;
            node->prev = p;
            node->next = p->next;
            p->next = node;
            list->len++;
            if (node->next != NULL) {
                node->next->prev = node;
            } else {
                list->last = node;
            }
        }
    }
}


void sort(struct List *list, int comparator(struct Person *p1, struct Person *p2)) {
    if (list == NULL) return;
    struct List *sorted = init();
    struct Node *p = list->first;
    while (p != NULL) {
        struct Node *tmp = p;
        p = p->next;
        unpin(list, tmp);
        insert_to_sorted_list(sorted, comparator, tmp);
    }
    list->first = sorted->first;
    list->last = sorted->last;
    list->len = sorted->len;
    free(sorted);
}

void sort_by_first_name(struct List *list) {
    sort(list, first_name_comparator);
}

void sort_by_last_name(struct List *list) {
    sort(list, last_name_comparator);
}

void sort_by_email(struct List *list) {
    sort(list, email_comparator);
}

void sort_by_phone(struct List *list) {
    sort(list, phone_comparator);
}

void sort_by_adress(struct List *list) {
    sort(list, adress_comparator);
}

void sort_by_birth(struct List *list) {
    sort(list, birth_date_comparator);
}

void print_forwards(struct List *list) {
    struct Node *p = list->first;
    while (p != NULL) {
        print_person(p->data);
        p = p->next;
    }
}

void print_backwards(struct List *list) {
    struct Node *p = list->last;
    while (p != NULL) {
        print_person(p->data);
        p = p->prev;
    }
}
