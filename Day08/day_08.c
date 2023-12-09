//
// Created by Fabian Metzger on 04.12.23.
//

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "../lib.h"
#include "day_08.h"


bool getDirection(Directions directions, int i) {
    const size_t directionLength = strlen(directions.direction);
    return directions.direction[i % directionLength] == 'R';
}

int day8_1(char input[]) {
    size_t inputLength = strlen(input);

    int offset = 0;
    char * directionsString = readUntilCharacter(input, '\n', &offset, 100);
    Directions directions = {directionsString};

    WayInstruction * wayInstructions = NULL;
    int numberOfWayInstructions = 0;

    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        size_t lineLength = strlen(line);
        if (lineLength > 0) {
            int lineOffset = 0;
            char * instruction = readUntilCharacter(line, ' ', &lineOffset, 20);
            lineOffset += 3;
            char * left = readUntilCharacter(line, ',', &lineOffset, 20);
            lineOffset += 1;
            char * right = readUntilCharacter(line, ')', &lineOffset, 20);

            wayInstructions = realloc(wayInstructions, (numberOfWayInstructions+1)*sizeof(WayInstruction));
            WayInstruction newWayInstruction = {instruction, left, right};
            wayInstructions[numberOfWayInstructions] = newWayInstruction;
            numberOfWayInstructions += 1;
        }
    }

    if (wayInstructions == NULL) {
        free(wayInstructions);
        return -1;
    }

    int i = 0;
    char * currentWaypoint = "AAA";
    while (strcmp(currentWaypoint, "ZZZ") != 0) {
        WayInstruction instruction;
        for (int j=0; j<numberOfWayInstructions; j++) {
            if (strcmp(currentWaypoint, wayInstructions[j].wayPoint) == 0) {
                instruction = wayInstructions[j];
            }
        }
        if (!getDirection(directions, i)) { // Left
            currentWaypoint = instruction.left;
        } else { // Right
            currentWaypoint = instruction.right;
        }
        i++;
    }

    free(wayInstructions);
    return i;
}

int day8_2(char input[]) {
    return -1;
}
