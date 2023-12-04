//
// Created by Fabian Metzger on 03.12.23.
//

#include <stdbool.h>

#ifndef AOC23_DAY_02_H
#define AOC23_DAY_02_H

typedef struct {
    int red;
    int green;
    int blue;
} BlockDraw;

typedef struct {
    int gameNumber;
    int numberOfDraws;
    BlockDraw * draws;
} DrawGame;

BlockDraw parseDraw(char text[]);
DrawGame parseLine(char line[]);
bool isGameValid(DrawGame game, int redAvailable, int greenAvailable, int blueAvailable);

int getGamePower(DrawGame game);

int day2_1(char input[]);
int day2_2(char input[]);

#endif //AOC23_DAY_02_H
