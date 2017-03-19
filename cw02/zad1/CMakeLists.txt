cmake_minimum_required(VERSION 2.8)
project(cw02)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c generator.c sorter_and_shuffler.c sorter_and_shuffler_sys.c)
add_executable(cw02 ${SOURCE_FILES})
