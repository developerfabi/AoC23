cmake_minimum_required(VERSION 3.26)
project(AoC23 C)

set(CMAKE_C_STANDARD 11)

include_directories(Day01)

add_executable(AoC23
        Day01/day_01.c
        Day01/day_01.h)
