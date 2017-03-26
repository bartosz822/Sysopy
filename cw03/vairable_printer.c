//
// Created by bartek on 25.03.17.
//
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    if(argc != 2 ){
        printf("Bad arguments");
        exit(2);
    }
    char* variable_name = argv[1];
    char* value = getenv(variable_name);
    if(value != NULL){
        printf("%s \n", value);
    } else {
        printf("nie ma takiej zmiennej");
    }
    exit(0);
}
