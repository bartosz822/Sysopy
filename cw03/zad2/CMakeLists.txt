cmake_minimum_required(VERSION 2.8)
project(cw03)

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
add_executable(vp vairable_printer.c)
add_executable(cw03 main_2.c.c)
add_executable(rh resource_hungry.c)
