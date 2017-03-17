#include <time.h>
#include <string.h>
#include "generator.h"
#include "sorter_and_shuffler.h"
#include "sorter_and_shuffler_sys.h"


int main(int argc, char* argv[]) {
    srand((unsigned int) time(NULL));


    if(argc != 6){
        printf("Bad arguments number");
        exit(EXIT_FAILURE);
    }

    char* file_name = argv[3];
    size_t records = (size_t) atoi(argv[4]);
    size_t bytes_per_record = (size_t) atoi(argv[5]);

    if (strcmp(argv[1],"lib") == 0){
        if(strcmp(argv[2], "generate") == 0){
            generate(file_name,records,bytes_per_record);
        } else if (strcmp(argv[2], "shuffle") == 0){
            shuffle(file_name,records,bytes_per_record);
        } else if (strcmp(argv[2], "sort") == 0){
            sort(file_name,records,bytes_per_record);
        } else {
            printf("Bad second argument");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(argv[1],"sys") == 0) {
        if(strcmp(argv[2], "generate") == 0){
            generate(file_name,records,bytes_per_record);
        } else if (strcmp(argv[2], "shuffle") == 0){
            shuffle_sys(file_name,records,bytes_per_record);
        } else if (strcmp(argv[2], "sort") == 0){
            sort_sys(file_name,records,bytes_per_record);
        } else {
            printf("Bad second argument");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Bad first argument");
        exit(EXIT_FAILURE);
    }

    return 0;
}