cmake_minimum_required(VERSION 3.26)
project(AoC23 C)

set(CMAKE_C_STANDARD 11)

include_directories(Day01)
include_directories(Day02)
include_directories(Day03)
include_directories(Day04)
include_directories(Day05)
include_directories(Day06)
include_directories(Day07)
include_directories(Day08)
include_directories(Day09)
include_directories(Day10)

add_executable(AoC23
        main.c
        main.h
        lib.c
        lib.h
        Day01/day_01.c
        Day01/day_01.h
        Day02/day_02.c
        Day02/day_02.h
        Day03/day_03.c
        Day03/day_03.h
        Day04/day_04.c
        Day04/day_04.h
        Day05/day_05.c
        Day05/day_05.h
        Day06/day_06.c
        Day06/day_06.h
        Day07/day_07.c
        Day07/day_07.h
        Day08/day_08.c
        Day08/day_08.h
        Day09/day_09.c
        Day09/day_09.h
        Day10/day_10.c
        Day10/day_10.h
)
