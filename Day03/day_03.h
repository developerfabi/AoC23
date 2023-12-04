//
// Created by Fabian Metzger on 03.12.23.
//

#ifndef AOC23_DAY_03_H
#define AOC23_DAY_03_H

typedef struct {
    int line;
    int index;
} TextPosition;

typedef struct {
    int partNumber;
    int line;
    int posStart;
    int length;
    bool hasAdjacentSymbol;
} MachinePart;

typedef struct {
    int numberOfParts;
    MachinePart * parts;
} Machine;

Machine getParts(char lineCurrent[]);
int getTotalPartNumber(char lineBefore[], char lineCurrent[], char lineAfter[]);

int day3_1(char input[]);
int day3_2(char input[]);

#endif //AOC23_DAY_03_H
