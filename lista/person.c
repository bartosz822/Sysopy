//
// Created by bartek on 09.03.17.
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "person.h"


int first_name_comparator(struct Person *p1, struct Person *p2) {
    return strcmp(p1->first_name, p2->first_name);
}

int last_name_comparator(struct Person *p1, struct Person *p2) {
    if (p1 == p2) return 0;
    return strcmp(p1->last_name, p2->last_name);
}

int birth_date_comparator(struct Person *p1, struct Person *p2) {
    return strcmp(p1->birth_date, p2->birth_date);
}

int email_comparator(struct Person *p1, struct Person *p2) {
    return strcmp(p1->email, p2->email);
}

int phone_comparator(struct Person *p1, struct Person *p2) {
    return strcmp(p1->phone, p2->phone);
}

int adress_comparator(struct Person *p1, struct Person *p2) {
    return strcmp(p1->adress, p2->adress);
}

void print_person(struct Person *p) {
    if (p == NULL) return;
    printf("%s ", p->first_name);
    printf("%s ", p->last_name);
    printf("%s ", p->birth_date);
    printf("%s ", p->email);
    printf("%s ", p->phone);
    printf("%s ", p->adress);
    printf("\n");
}

struct Person *
create_person(char *first_name, char *last_name, char *birth_date, char *email, char *phone, char *adress) {

    struct Person *newPerson = (struct Person *) malloc(sizeof(Person));
    char *first_name2 = (char *) malloc(strlen(first_name) * sizeof(char) + 1);
    char *last_name2 = (char *) malloc(strlen(last_name) * sizeof(char) + 1);
    char *birth_date2 = (char *) malloc(strlen(birth_date) * sizeof(char) + 1);
    char *email2 = (char *) malloc(strlen(email) * sizeof(char) + 1);
    char *phone2 = (char *) malloc(strlen(phone) * sizeof(char) + 1);
    char *adress2 = (char *) malloc(strlen(adress) * sizeof(char) + 1);

    strcpy(first_name2, first_name);
    strcpy(last_name2, last_name);
    strcpy(birth_date2, birth_date);
    strcpy(email2, email);
    strcpy(phone2, phone);
    strcpy(adress2, adress);

    newPerson->first_name = first_name2;
    newPerson->last_name = last_name2;
    newPerson->birth_date = birth_date2;
    newPerson->email = email2;
    newPerson->phone = phone2;
    newPerson->adress = adress2;
    return newPerson;
};

void kill_person(struct Person *person) {
    free(person->first_name);
    free(person->last_name);
    free(person->adress);
    free(person->email);
    free(person->birth_date);
    free(person->phone);
    free(person);
}