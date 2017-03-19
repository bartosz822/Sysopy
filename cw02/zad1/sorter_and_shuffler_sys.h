//
// Created by bartek on 17.03.17.
//

#ifndef CW02_SORTER_AND_SHUFFLER_SYS_H
#define CW02_SORTER_AND_SHUFFLER_SYS_H
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <fcntl.h>

void shuffle_sys(char* file_name, size_t records, size_t bytes_per_record);
void sort_sys(char* file_name, size_t records, size_t bytes_per_record);


#endif //CW02_SORTER_AND_SHUFFLER_SYS_H
