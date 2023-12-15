//
// Created by Fabian Metzger on 11.12.23.
//

#include <stdio.h>
#include "day_14.h"
#include "../lib.h"

int northernmostPosition(Pattern pattern, int row, int column) {
    int intermediateRocks = 0;
    for (int i=row-1; i>=0; i--) {
        if (pattern.matrix[i][column] == 'O') intermediateRocks += 1;
        else if (pattern.matrix[i][column] == '#') {
            printf("Blocked rock (row %d) with %d intermediate from %d in column %d -> %d\n",
                   i, intermediateRocks, row, column, pattern.height - i - intermediateRocks - 1);
            return pattern.height - i - intermediateRocks - 1;
        }
    }
    printf("Free rock with %d intermediate from %d in column %d -> %d\n",
           intermediateRocks, row, column, pattern.height - intermediateRocks);
    return pattern.height - intermediateRocks;
}

int64_t calculateLoad(Pattern pattern) {
    int64_t total = 0;
    for (int i=0; i<pattern.width*pattern.height; i++) {
        int indexColumn = i % pattern.width;
        int indexRow = (i - indexColumn) / pattern.width;
        if (pattern.matrix[indexRow][indexColumn] == 'O') {
            total += pattern.height - indexRow;
        }
    }
    return total;
}

void rollNorth(Pattern * pattern) {
    for (int col=0; col<pattern->width; col++) {
        int lastStop = 0;
        for (int row=0; row<pattern->height; row++) {
            if (pattern->matrix[row][col] == '#') lastStop = row + 1;
            else if (pattern->matrix[row][col] == 'O') {
                pattern->matrix[row][col] = '.';
                pattern->matrix[lastStop][col] = 'O';
                lastStop += 1;
            }
        }
    }
}

void rollSouth(Pattern * pattern) {
    for (int col=0; col<pattern->width; col++) {
        int lastStop = pattern->height-1;
        for (int row = pattern->height-1; row>=0; row--) {
            if (pattern->matrix[row][col] == '#') lastStop = row - 1;
            else if (pattern->matrix[row][col] == 'O') {
                pattern->matrix[row][col] = '.';
                pattern->matrix[lastStop][col] = 'O';
                lastStop -= 1;
            }
        }
    }
}

void rollEast(Pattern * pattern) {
    for (int row=0; row<pattern->height; row++) {
        int lastStop = pattern->width-1;
        for (int col = pattern->width-1; col>=0; col--) {
            if (pattern->matrix[row][col] == '#') lastStop = col - 1;
            else if (pattern->matrix[row][col] == 'O') {
                pattern->matrix[row][col] = '.';
                pattern->matrix[row][lastStop] = 'O';
                lastStop -= 1;
            }
        }
    }
}

void rollWest(Pattern * pattern) {
    for (int row=0; row<pattern->height; row++) {
        int lastStop = 0;
        for (int col=0; col < pattern->width; col++) {
            if (pattern->matrix[row][col] == '#') lastStop = col + 1;
            else if (pattern->matrix[row][col] == 'O') {
                pattern->matrix[row][col] = '.';
                pattern->matrix[row][lastStop] = 'O';
                lastStop += 1;
            }
        }
    }
}

int64_t day14_1(char input[]) {
    Pattern pattern = parsePattern(input);

    int64_t total = 0;
    for (int i=0; i<pattern.width*pattern.height; i++) {
        int indexColumn = i % pattern.width;
        int indexRow = (i - indexColumn) / pattern.width;
        if (pattern.matrix[indexRow][indexColumn] == 'O') {
            total += northernmostPosition(pattern, indexRow, indexColumn);
        }
    }
    return total;
}

int64_t day14_2(char input[]) {
    Pattern pattern = parsePattern(input);

    Hashtable hashtable;
    initializeHashtable(&hashtable);

    const int64_t LIMIT = 1000;
    for (int64_t i=0; i<LIMIT; i++) {
        rollNorth(&pattern);
        rollWest(&pattern);
        rollSouth(&pattern);
        rollEast(&pattern);
        printf("Rolled cycle %lld", i);

        char * printedPattern = printPattern(pattern);
        HashElement * element = search(&hashtable, printedPattern);
        if (element != NULL) {
            int64_t delta = i-element->content;
            int64_t deltaTimes = (LIMIT-i) / delta;
            if (i+delta < LIMIT) {
                i += deltaTimes * delta;
                printf(" [Skipping %lld*%lld]\n", deltaTimes, delta);
            }
        } else {
            HashElement element = {printedPattern, i};
            insert(&hashtable, &element);
        }
    }
    return calculateLoad(pattern);
}