//
// Created by Fabian Metzger on 11.12.23.
//

#ifndef AOC23_DAY_14_H
#define AOC23_DAY_14_H

#include <stdint.h>
#include "../lib.h"

int northernmostPosition(Pattern pattern, int row, int column);

int64_t calculateLoad(Pattern pattern);

void rollNorth(Pattern * pattern);
void rollSouth(Pattern * pattern);
void rollEast(Pattern * pattern);
void rollWest(Pattern * pattern);

int64_t day14_1(char input[]);
int64_t day14_2(char input[]);

#endif //AOC23_DAY_14_H
