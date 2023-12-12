//
// Created by Fabian Metzger on 11.12.23.
//

#ifndef AOC23_DAY_11_H
#define AOC23_DAY_11_H

#include <stdint.h>

typedef struct {
    int posVertical;
    int posHorizontal;
} Galaxy;

typedef struct {
    Galaxy * galaxies;
    int numberOfGalaxies;
    int height;
    int width;
    int * emptyLines;
    int * emptyColumns;
    int numberOfEmptyLines;
    int numberOfEmptyColumns;
} Universe;

Universe parseUniverse(char input[]);

void calculateEmptySpace(Universe * universe);

int64_t calculateDistance(Galaxy first, Galaxy second, Universe universe, int expansion);

int64_t day11_1(char input[]);
int64_t day11_2(char input[]);

#endif //AOC23_DAY_11_H
