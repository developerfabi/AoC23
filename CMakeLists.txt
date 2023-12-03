cmake_minimum_required(VERSION 3.26)
project(AoC23 C)

set(CMAKE_C_STANDARD 11)

include_directories(Day01)
include_directories(Day02)
include_directories(Day03)

add_executable(AoC23
        main.c
        main.h
        Day01/day_01.c
        Day01/day_01.h
        Day02/day_02.c
        Day02/day_02.h
        Day03/day_03.c
        Day03/day_03.h)
