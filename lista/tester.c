//
// Created by bartek on 08.03.17.
//

#define _GNU_SOURCE

#include <string.h>
#include "list.h"
#include "tree.h"
#include <time.h>
#include <sys/times.h>


void people_from_csv(void *p, void insertFunction(void *, void *), void *creation_function(void *)) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("./data.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1) {
        char *first_name = strtok(line, ",");
        char *last_name = strtok(NULL, ",");
        char *birth = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *phone = strtok(NULL, ",");
        char *adress = strtok(NULL, ",");
        struct Person *new = create_person(first_name, last_name, birth, email, phone, adress);
        insertFunction(p, creation_function(new));
    }

    fclose(fp);
    if (line)
        free(line);
}


struct List *list1000() {
    struct List *list = init();
    people_from_csv(list, (void (*)(void *, void *)) insert_to_beggining_list, (void *(*)(void *)) create_node);
    return list;
};


struct Tree *tree1000() {
    struct Tree *tree = init_tree();
    people_from_csv(tree, (void (*)(void *, void *)) insert, (void *(*)(void *)) create_tree_node);
    return tree;
}


clock_t start_time;
clock_t prev_time;
clock_t a_time;
static struct tms start_tms;
static struct tms last_tms;
static struct tms a_tms;

void set_start_time() {
    start_time = prev_time = clock();
    times(&start_tms);
    last_tms = start_tms;
}

void print_times() {
    times(&a_tms);
    a_time = clock();
    printf("real\t from last print= %.6lf, from start = %.6lf\n",
           (double) (a_time - prev_time) / CLOCKS_PER_SEC, (double) (a_time - start_time) / CLOCKS_PER_SEC);
    printf("user\t from last print= %.6lf, from start = %.6lf\n",
           (double) (a_tms.tms_utime - last_tms.tms_utime) / CLOCKS_PER_SEC,
           (double) (a_tms.tms_utime - start_tms.tms_utime) / CLOCKS_PER_SEC);
    printf("system\t from last print= %.6lf, from start = %.6lf\n",
           (double) (a_tms.tms_stime - last_tms.tms_stime) / CLOCKS_PER_SEC,
           (double) (a_tms.tms_stime - start_tms.tms_stime) / CLOCKS_PER_SEC);
    prev_time = a_time;
    last_tms = a_tms;
    printf("----------------------**************---------------------\n");
}


void tree_benchmark() {
    set_start_time();
    printf("----------------------TREE_BENCHMARK---------------------\n");
    printf("--------------------------start--------------------------\n");
    print_times();
    printf("----------------------tree_creation----------------------\n");
    struct Tree *tree = init_tree();
    print_times();
    printf("--------------------adding_one_element-------------------\n");
    insert(tree, create_tree_node(
            create_person("Andrzej", "Kowalski", "01/01/1996", "a@b.com", "123456789", "ul. Jakas 8 Gdzies")));
    print_times();
    printf("-------------------adding_1000_elements------------------\n");
    people_from_csv(tree, (void (*)(void *, void *)) insert, (void *(*)(void *)) create_tree_node);
    print_times();
    printf("----------------------find_optimistic--------------------\n");
    find_person_tree(tree, "Andrzej", "Kowalski");
    print_times();
    printf("---------------------find_pesimistic---------------------\n");
    find_person_tree(tree, "Willie", "Banks");
    printf("---------------------remove_pesimistic-------------------\n");
    delete_person_tree(tree, "Andrzej", "Kowalski");
    print_times();
    printf("---------------------remove_optimistic-------------------\n");
    delete_person_tree(tree, "Aaron", "Hansen");
    print_times();
    printf("-----------------------rebuild_tree----------------------\n");
    rebuild_tree(tree, last_name_comparator);
    print_times();
    delete_tree(tree);
    printf("-------------------END_OF_TREE_BENCHMARK-----------------\n\n");
}

void list_benchmark() {
    set_start_time();
    printf("----------------------LIST_BENCHMARK---------------------\n");
    printf("--------------------------start--------------------------\n");
    print_times();
    printf("----------------------list_creation----------------------\n");
    struct List* list = init();
    print_times();
    printf("--------------------adding_one_element-------------------\n");
    insert_to_beggining_list(list, create_node(
            create_person("Andrzej", "Kowalski", "01/01/1996", "a@b.com", "123456789", "ul. Jakas 8 Gdzies")));
    print_times();
    printf("-------------------adding_1000_elements------------------\n");
    people_from_csv(list, (void (*)(void *, void *)) insert_to_beggining_list, (void *(*)(void *)) create_node);
    print_times();
    printf("----------------------find_optimistic--------------------\n");
    find_person(list, "Randy", "Wood");
    print_times();
    printf("---------------------find_pesimistic---------------------\n");
    find_person(list, "Andrzej", "Kowalski");
    printf("---------------------remove_pesimistic-------------------\n");
    delete_person(list, "Andrzej", "Kowalski");
    print_times();
    printf("---------------------remove_optimistic-------------------\n");
    delete_person(list, "Randy", "Wood");
    print_times();
    printf("------------------------sort_list------------------------\n");
    sort_by_last_name(list);
    print_times();
    delete_list(list);
    printf("-------------------END_OF_LIST_BENCHMARK-----------------\n\n");
}

