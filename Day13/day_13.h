//
// Created by Fabian Metzger on 11.12.23.
//

#ifndef AOC23_DAY_13_H
#define AOC23_DAY_13_H

#include <stdint.h>

typedef struct {
    char ** matrix;
    int height;
    int width;
} Pattern;

Pattern parsePattern(char * input);

void toggleSymbol(Pattern * pattern, int row, int column);

int checkForHorizontalReflection(Pattern pattern);
int checkForHorizontalReflectionWithException(Pattern pattern, int exception);
int checkForVerticalReflection(Pattern pattern);
int checkForVerticalReflectionWithException(Pattern pattern, int exception);

int64_t day13_1(char input[]);
int64_t day13_2(char input[]);

#endif //AOC23_DAY_13_H
