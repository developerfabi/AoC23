//
// Created by Fabian Metzger on 04.12.23.
//

#ifndef AOC23_DAY_06_H
#define AOC23_DAY_06_H

typedef struct {
    int64_t minimum;
    int64_t maximum;
} Range;

Range getWinningRange(int64_t time, int64_t record);

int64_t day6_1(char input[]);
int64_t day6_2(char input[]);

#endif //AOC23_DAY_06_H
