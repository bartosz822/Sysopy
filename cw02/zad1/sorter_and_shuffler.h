//
// Created by bartek on 17.03.17.
//

#ifndef CW02_SORTER_AND_SHUFFLER_H
#define CW02_SORTER_AND_SHUFFLER_H

#include <stdio.h>
#include <stdlib.h>

void sort(char* file_name, size_t records, size_t bytes_per_record);
void shuffle(char* file_name, size_t records, size_t bytes_per_record);

#endif //CW02_SORTER_AND_SHUFFLER_H
