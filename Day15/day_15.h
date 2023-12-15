//
// Created by Fabian Metzger on 11.12.23.
//

#ifndef AOC23_DAY_15_H
#define AOC23_DAY_15_H

#include <stdint.h>

typedef struct LavaLens {
    char * label;
    int focalLength;
    struct LavaLens * nextLens;
} LavaLens;

typedef struct {
    LavaLens ** firstLens;
} LensBoxCollection;

void insertLens(LensBoxCollection * lensBoxCollection, char * label, int focalLength);
void removeLens(LensBoxCollection * lensBoxCollection, char * label);

void processInstruction(LensBoxCollection * lensBoxCollection, char * instruction);

int64_t calculateFocalPower(LensBoxCollection lensBoxCollection);

int64_t createHash(char * input);

int64_t day15_1(char input[]);
int64_t day15_2(char input[]);

#endif //AOC23_DAY_15_H
