//
// Created by bartek on 17.03.17.
//
#include "sorter_and_shuffler.h"

void check_read_error(size_t result, size_t count){
    if(result != count){
        perror("Error while reading the file!");
        exit(EXIT_FAILURE);
    }
}

void check_write_error(size_t result, size_t count){
    if(result != count){
        perror("Error while writing the file!");
        exit(EXIT_FAILURE);
    }
}

void swap_in_file(FILE* file, size_t i, size_t j, size_t bytes_per_record){
    void* tmp1 = malloc(bytes_per_record);
    void* tmp2 = malloc(bytes_per_record);

    fseek(file, i*bytes_per_record, SEEK_SET);
    size_t result = fread(tmp1, bytes_per_record, 1, file);
    check_read_error(result, 1);

    fseek(file, j*bytes_per_record, SEEK_SET);
    result = fread(tmp2, bytes_per_record, 1, file);
    check_read_error(result, 1);

    fseek(file, i*bytes_per_record, SEEK_SET);
    result = fwrite(tmp2, bytes_per_record, 1, file);
    check_write_error(result, 1);

    fseek(file, j*bytes_per_record, SEEK_SET);
    result = fwrite(tmp1, bytes_per_record, 1, file);
    check_write_error(result, 1);

    free(tmp1);
    free(tmp2);
}

void shuffle(char* file_name, size_t records, size_t bytes_per_record){

    FILE* file = fopen(file_name, "r+");

    if(file == NULL){
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }


    for (size_t i = 0; i < records; ++i) {
        size_t j = rand() % records;
        swap_in_file(file,i,j,bytes_per_record);
    }

    fclose(file);

}

void sort(char* file_name, size_t records, size_t bytes_per_record){

    FILE* file = fopen(file_name, "r+");

    if(file == NULL){
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < records-1; ++i) {
        for (size_t j = 0; j < records - i -1; ++j) {
            unsigned char* key1 = malloc(sizeof(unsigned char));
            unsigned char* key2 = malloc(sizeof(unsigned char));

            fseek(file, j*bytes_per_record, SEEK_SET);
            size_t result = fread(key1,1,1, file);
            check_read_error(result, 1);

            fseek(file, (j+1)*bytes_per_record, SEEK_SET);
            result = fread(key2, 1,1, file);
            check_read_error(result, 1);

            if((*key1)>(*key2)){
                swap_in_file(file,j,j+1,bytes_per_record);
            }
            free(key1);
            free(key2);
        }


    }

    fclose(file);
}

