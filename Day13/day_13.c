//
// Created by Fabian Metzger on 11.12.23.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "day_13.h"
#include "../lib.h"

Pattern parsePattern(char * input) {
    size_t inputLength = strlen(input);

    Pattern pattern = {NULL, 0, -1};

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        int width = strlen(line);

        pattern.matrix = realloc(pattern.matrix, (pattern.height+1) * sizeof(char *));
        pattern.matrix[pattern.height] = line;
        pattern.height += 1;
        pattern.width = (pattern.width > width || pattern.width<0) ? width : pattern.width;
    }

    return pattern;
}

void toggleSymbol(Pattern * pattern, int row, int column) {
    if (pattern->matrix[row][column] == '.') pattern->matrix[row][column] = '#';
    else if (pattern->matrix[row][column] == '#') pattern->matrix[row][column] = '.';
}

int checkForHorizontalReflection(Pattern pattern) {
    return checkForHorizontalReflectionWithException(pattern, -1);
}

int checkForHorizontalReflectionWithException(Pattern pattern, int exception) {
    for (int row=0; row<(pattern.height-1); row++) {
        bool mirrored = true;
        for (int back=0; back<(pattern.height-row-1) && back<=row; back++) {
            if (strcmp(pattern.matrix[row+back+1], pattern.matrix[row-back]) != 0) {
                mirrored = false;
                back = row;
            }
        }
        if (mirrored && row != exception) return row;
    }
    return -1;
}

int checkForVerticalReflection(Pattern pattern) {
    return checkForVerticalReflectionWithException(pattern, -1);
}

int checkForVerticalReflectionWithException(Pattern pattern, int exception) {
    for (int column=0; column<(pattern.width-1); column++) {
        bool mirrored = true;
        for (int back=0; back<(pattern.width-column-1) && back<=column; back++) {
            for (int i=0; i<pattern.height; i++) {
                if (pattern.matrix[i][column+back+1] != pattern.matrix[i][column-back]) {
                    mirrored = false;
                    i = pattern.height;
                    back = (column+1);
                }
            }
        }
        if (mirrored && column != exception) return column;
    }
    return -1;
}

int64_t day13_1(char input[]) {
    size_t inputLength = strlen(input);

    int64_t total = 0;

    int offset = 0;
    while (offset < inputLength) {
        char * field = readUntilEmptyLine(input, &offset, 100);
        Pattern pattern = parsePattern(field);

        int vertical = checkForVerticalReflection(pattern);
        if (vertical >= 0) total += (vertical+1);
        else {
            int horizontal = checkForHorizontalReflection(pattern);
            if (horizontal >= 0) total += (100 * (horizontal+1));
        }
    }

    return total;
}

int64_t day13_2(char input[]) {
    size_t inputLength = strlen(input);

    int64_t total = 0;

    int offset = 0;
    while (offset < inputLength) {
        char * field = readUntilEmptyLine(input, &offset, 100);
        Pattern pattern = parsePattern(field);

        int oldVertical = checkForVerticalReflection(pattern);
        int oldHorizontal = checkForHorizontalReflection(pattern);
        bool found = false;

        for (int i=0; i<pattern.width*pattern.height && !found; i++) {
            int indexColumn = i % pattern.width;
            int indexRow = (i-indexColumn)/pattern.width;
            toggleSymbol(&pattern, indexRow, indexColumn);

            int vertical = checkForVerticalReflectionWithException(pattern, oldVertical);
            if (vertical >= 0 && vertical != oldVertical) {
                printf("Adding vertical %d (with change at %d,%d)\n", (vertical+1), indexRow, indexColumn);
                total += (vertical+1);
                found = true;
            }
            else {
                int horizontal = checkForHorizontalReflectionWithException(pattern, oldHorizontal);
                if (horizontal >= 0 && horizontal != oldHorizontal) {
                    printf("Adding horizontal %d (with change at %d,%d)\n", (horizontal+1), indexRow, indexColumn);
                    total += (100 * (horizontal+1));
                    found = true;
                }
            }

            toggleSymbol(&pattern, indexRow, indexColumn);
        }

        if (!found) {
            printf("Found no mirror\n");
        }
    }

    return total;
}
