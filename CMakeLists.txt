cmake_minimum_required(VERSION 3.16)
project(GuitarCatalog C)

set(CMAKE_C_STANDARD 99)

add_executable(GuitarCatalog main.c list.c list.h data.c data.h menu.c menu.h)