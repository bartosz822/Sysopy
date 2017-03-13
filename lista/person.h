//
// Created by bartek on 09.03.17.
//

#ifndef LISTA_PERSON_H
#define LISTA_PERSON_H

#include "list.h"

struct Person {
    char *first_name;
    char *last_name;
    char *birth_date;
    char *email;
    char *phone;
    char *adress;
} Person;

int first_name_comparator(struct Person *p1, struct Person *p2);

int last_name_comparator(struct Person *p1, struct Person *p2);

int birth_date_comparator(struct Person *p1, struct Person *p2);

int email_comparator(struct Person *p1, struct Person *p2);

int phone_comparator(struct Person *p1, struct Person *p2);

int adress_comparator(struct Person *p1, struct Person *p2);

void print_person(struct Person *p);

struct Person *
create_person(char *first_name, char *last_name, char *birth_date, char *email, char *phone, char *adress);

void kill_person(struct Person *person);


#endif //LISTA_PERSON_H
