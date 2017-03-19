cmake_minimum_required(VERSION 2.8)
project(zad2)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(zad2 ${SOURCE_FILES})
add_executable(zad2_nftw main_nftw.c)