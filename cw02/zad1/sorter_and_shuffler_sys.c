//
// Created by bartek on 17.03.17.
//


#include "sorter_and_shuffler_sys.h"


void check_read_error_sys(ssize_t result, size_t count){
    if(result != count){
        perror("Error while reading the file!");
        exit(EXIT_FAILURE);
    }
}

void check_write_error_sys(ssize_t result, size_t count){
    if(result != count){
        perror("Error while writing the file!");
        exit(EXIT_FAILURE);
    }
}

void swap_in_file_sys(int file, size_t i, size_t j, size_t bytes_per_record){
    void* tmp1 = malloc(bytes_per_record);
    void* tmp2 = malloc(bytes_per_record);


    lseek(file, i*bytes_per_record, SEEK_SET);
    ssize_t result = read(file,tmp1, bytes_per_record);
    check_read_error_sys(result, bytes_per_record);

    lseek(file, j*bytes_per_record, SEEK_SET);
    result = read(file,tmp2, bytes_per_record);
    check_read_error_sys(result, bytes_per_record);

    lseek(file, j*bytes_per_record, SEEK_SET);
    result = write(file,tmp1, bytes_per_record);
    check_write_error_sys(result, bytes_per_record);

    lseek(file, i*bytes_per_record, SEEK_SET);
    result = write(file,tmp2, bytes_per_record);
    check_write_error_sys(result, bytes_per_record);

    free(tmp1);
    free(tmp2);
}

void shuffle_sys(char* file_name, size_t records, size_t bytes_per_record){

    int file = open(file_name, O_RDWR);

    if(file == 0){
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }


    for (size_t i = 0; i < records; ++i) {
        size_t j = rand() % records;
        swap_in_file_sys(file, i, j, bytes_per_record);
    }

    close(file);

}

void sort_sys(char* file_name, size_t records, size_t bytes_per_record){

    int file = open(file_name, O_RDWR);

    if(file == 0){
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < records-1; ++i) {
        for (size_t j = 0; j < records - i -1; ++j) {
            unsigned char* key1 = malloc(sizeof(unsigned char));
            unsigned char* key2 = malloc(sizeof(unsigned char));

            lseek(file, j*bytes_per_record, SEEK_SET);
            ssize_t result = read(file,key1, 1);
            check_read_error_sys(result, 1);

            lseek(file, (j+1)*bytes_per_record, SEEK_SET);
            result = read(file,key2, 1);
            check_read_error_sys(result, 1);

            if((*key1)>(*key2)){
                swap_in_file_sys(file, j, j + 1, bytes_per_record);
            }
            free(key1);
            free(key2);
        }


    }

    close(file);
}

