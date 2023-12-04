//
// Created by Fabian Metzger on 03.12.23.
//
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "day_02.h"
#include "../lib.h"

#define RED_AVAILABLE 12
#define GREEN_AVAILABLE 13
#define BLUE_AVAILABLE 14

BlockDraw parseDraw(char text[]) {
    size_t textLength = strlen(text);
    BlockDraw draw;
    draw.red = 0;
    draw.green = 0;
    draw.blue = 0;

    char * number = (char *) malloc(6 * sizeof(char));
    memset(number, '\0', 6);
    int numberIndex = 0;
    char * color = (char *) malloc(6 * sizeof(char));
    memset(color, '\0', 6);
    int colorIndex = 0;

    for (int i = 0; i <= textLength; i++) {
        if (i >= textLength || text[i] == ',') {
            int count = atoi(number);
            if (count >= 0) {
                if (strstr(color, "red") != NULL) draw.red = count;
                if (strstr(color, "green") != NULL) draw.green = count;
                if (strstr(color, "blue") != NULL) draw.blue = count;
            }
            memset(number, '\0', 6);
            numberIndex = 0;
            memset(color, '\0', 6);
            colorIndex = 0;
        } else if (isdigit(text[i])) {
            if (numberIndex < 5) {
                number[numberIndex] = text[i];
                numberIndex ++;
            }
        } else {
            if (colorIndex < 5 && text[i] != ' ') {
                color[colorIndex] = text[i];
                colorIndex ++;
            }
        }
    }

    return draw;
}

DrawGame parseLine(char line[]) {
    size_t inputLength = strlen(line);

    int offset = 5;

    DrawGame game;
    char * gameNumber = readUntilCharacter(line, ':', &offset, 10);
    game.gameNumber = atoi(gameNumber);
    game.numberOfDraws = 0;
    game.draws = NULL;

    offset += 1;
    while (offset < inputLength) {
        char * drawString = readUntilCharacter(line, ';', &offset, 100);
        BlockDraw draw = parseDraw(drawString);
        free(drawString);

        game.draws = realloc(game.draws, (game.numberOfDraws + 1) * sizeof(BlockDraw));
        game.draws[game.numberOfDraws] = draw;
        game.numberOfDraws += 1;
    }

    return game;
}

bool isGameValid(DrawGame game, int redAvailable, int greenAvailable, int blueAvailable) {
    for (int i = 0; i < game.numberOfDraws; i++) {
        if (
            game.draws[i].red > redAvailable
            || game.draws[i].green > greenAvailable
            || game.draws[i].blue > blueAvailable
        ) return false;
    }
    return true;
}

int getGamePower(DrawGame game) {
    int minRed = 0;
    int minGreen = 0;
    int minBlue = 0;

    for (int i = 0; i < game.numberOfDraws; i++) {
        if (game.draws[i].red > minRed) minRed = game.draws[i].red;
        if (game.draws[i].green > minGreen) minGreen = game.draws[i].green;
        if (game.draws[i].blue > minBlue) minBlue = game.draws[i].blue;
    }

    return minRed * minGreen * minBlue;
}

int day2_1(char input[]) {
    size_t inputLength = strlen(input);
    int total = 0;

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        DrawGame game = parseLine(line);
        free(line);

        if (isGameValid(game, RED_AVAILABLE, GREEN_AVAILABLE, BLUE_AVAILABLE)) {
            total += game.gameNumber;
            printf("-> Including game %d\n", game.gameNumber);
        }
    }

    return total;
}

int day2_2(char input[]) {
    size_t inputLength = strlen(input);
    int total = 0;

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        DrawGame game = parseLine(line);
        free(line);

        total += getGamePower(game);
    }

    return total;
}
