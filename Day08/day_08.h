//
// Created by Fabian Metzger on 04.12.23.
//

#ifndef AOC23_DAY_08_H
#define AOC23_DAY_08_H
#include <stdbool.h>

typedef struct {
    char * wayPoint;
    char * left;
    char * right;
} WayInstruction;

typedef struct {
    char * direction;
} Directions;

typedef struct {
    Directions directions;
    WayInstruction * wayInstructions;
    int numberOfWayInstructions;
} Route;

Route parseRoute(char input[]);

bool getDirection(Directions directions, int64_t i);

int64_t day8_1(char input[]);
int64_t day8_2(char input[]);

#endif //AOC23_DAY_08_H
