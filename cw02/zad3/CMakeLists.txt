cmake_minimum_required(VERSION 2.8)
project(zad3)

macro(use_c11)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_C_FLAGS "--std=gnu11 ${CMAKE_C_FLAGS}")
        endif ()
    else ()
        set (CMAKE_C_STANDARD 11)
    endif ()
endmacro(use_c11)


use_c11()

set(SOURCE_FILES main.c)
add_executable(zad3 ${SOURCE_FILES})


