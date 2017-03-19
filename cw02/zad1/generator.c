//
// Created by bartek on 17.03.17.
//

#include "generator.h"

void* get_random_record(FILE* file, size_t bytes_per_record) {

    void* buffer = malloc(bytes_per_record);
    size_t result = fread(buffer, bytes_per_record, 1, file);

    if(result == 0){
        perror("Error while reading the file!");
        exit(EXIT_FAILURE);
    }

    return buffer;
}


void generate(char* file_name, size_t records, size_t bytes_per_record){
    FILE* write_file;
    write_file = fopen(file_name,"w");

    FILE * read_file;
    read_file = fopen("/dev/random", "r");


    if (write_file == NULL) {
        perror("Error while crating the file!");
        exit(EXIT_FAILURE);
    } else if( read_file == NULL){
        perror("Error while reading the file!");
        exit(EXIT_FAILURE);
    }

    void* buffer;
    for (int i = 0; i < records; ++i) {
        buffer = get_random_record(read_file, bytes_per_record);
        fwrite(buffer, bytes_per_record, 1, write_file);
        free(buffer);
    }

    fclose(read_file);
    fclose(write_file);

}