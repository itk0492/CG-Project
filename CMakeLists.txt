cmake_minimum_required(VERSION 3.6)
project(final3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c rasterizer.c rasterizer.h objLists.c objLists.h transformations.c transformations.h)
add_executable(final3 ${SOURCE_FILES} rasterizer.c rasterizer.h objLists.c objLists.h transformations.c transformations.h)