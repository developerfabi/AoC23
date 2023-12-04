//
// Created by Fabian Metzger on 03.12.23.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "../lib.h"
#include "day_03.h"

Machine getParts(char lineCurrent[]) {
    size_t lineCurrentLength = strlen(lineCurrent);

    Machine machine;
    machine.numberOfParts = 0;
    machine.parts = NULL;

    char * numberBuffer = (char *) malloc(33 * sizeof(char));
    memset(numberBuffer, '\0', 33);
    int numberBufferIndex = 0;

    for (int i=0; i <= lineCurrentLength; i++) {
        if (i >= lineCurrentLength || !isdigit(lineCurrent[i])) {
            if (numberBufferIndex > 0) {
                int number = atoi(numberBuffer);

                machine.parts = realloc(machine.parts, (machine.numberOfParts + 1) * sizeof(MachinePart));
                machine.parts[machine.numberOfParts].partNumber = number;
                machine.parts[machine.numberOfParts].length = strlen(numberBuffer);
                machine.parts[machine.numberOfParts].posStart = i - machine.parts[machine.numberOfParts].length;
                machine.numberOfParts += 1;

                memset(numberBuffer, '\0', 33);
                numberBufferIndex = 0;
            }
        } else {
            if (numberBufferIndex < 32) {
                numberBuffer[numberBufferIndex] = lineCurrent[i];
                numberBufferIndex ++;
            }
        }
    }

    return machine;
}

int getTotalPartNumber(char lineBefore[], char lineCurrent[], char lineAfter[]) {
    size_t lineBeforeLength = 0;
    size_t lineCurrentLength = strlen(lineCurrent);;
    size_t lineAfterLength = 0;

    if (lineBefore != NULL) lineBeforeLength = strlen(lineBefore);
    if (lineAfter != NULL) lineAfterLength = strlen(lineAfter);

    printf("Reading line %s\n", lineCurrent);
    Machine machine = getParts(lineCurrent);

    int total = 0;
    for (int i=0; i < machine.numberOfParts; i++) {
        bool hasAdjacentSymbol = false;
        int indexStart = machine.parts[i].posStart - 1;
        int indexEnd = machine.parts[i].posStart + machine.parts[i].length;

        if (indexStart >= 0 && indexStart < lineCurrentLength) {
            char charBefore = lineCurrent[indexStart];
            if (charBefore != '.' && !isdigit(charBefore)) hasAdjacentSymbol = true;
        }
        if (indexEnd >= 0 && indexEnd < lineCurrentLength) {
            char charAfter = lineCurrent[indexEnd];
            if (charAfter != '.' && !isdigit(charAfter)) hasAdjacentSymbol = true;
        }

        if (!hasAdjacentSymbol) {
            for (int j = indexStart; j <= indexEnd; j++) {
                if (j >= 0 && j < lineBeforeLength) {
                    if (lineBefore[j] != '.' && !isdigit(lineBefore[j])) hasAdjacentSymbol = true;
                }
                if (j >= 0 && j < lineAfterLength) {
                    if (lineAfter[j] != '.' && !isdigit(lineAfter[j])) hasAdjacentSymbol = true;
                }
            }
        }

        if (hasAdjacentSymbol) {
            total += machine.parts[i].partNumber;
            printf("-> Including part %d\n", machine.parts[i].partNumber);
        }
    }

    return total;
}

int day3_1(char input[]) {
    size_t inputLength = strlen(input);
    int total = 0;

    char * lineBefore = NULL;
    char * lineCurrent = NULL;
    char * lineAfter = NULL;

    int offset = 0;
    while (offset < inputLength || lineAfter != NULL) {
        free(lineBefore);
        lineBefore = lineCurrent;
        lineCurrent = lineAfter;
        if (offset < inputLength) {
            lineAfter = readUntilCharacter(input, '\n', &offset, 100);
        } else {
            lineAfter = NULL;
        }

        if (lineCurrent != NULL) {
            total += getTotalPartNumber(lineBefore, lineCurrent, lineAfter);
        }
    }

    return total;
}

int day3_2(char input[]) {
    size_t inputLength = strlen(input);
    Machine machine;
    machine.numberOfParts = 0;
    machine.parts = NULL;

    TextPosition * gearPositions = NULL;
    int numberOfGearPositions = 0;

    int offset = 0;
    int lineNumber = 0;
    while (offset < inputLength) {
        char * lineCurrent = readUntilCharacter(input, '\n', &offset, 100);

        for (int i=0; i < strlen(lineCurrent); i++) {
            if (lineCurrent[i] == '*') {
                gearPositions = realloc(gearPositions, (numberOfGearPositions + 1) * sizeof(TextPosition));
                gearPositions[numberOfGearPositions].line = lineNumber;
                gearPositions[numberOfGearPositions].index = i;
                numberOfGearPositions += 1;
            }
        }

        Machine newMachine = getParts(lineCurrent);
        machine.parts = realloc(machine.parts, (machine.numberOfParts + newMachine.numberOfParts) * sizeof(MachinePart));
        for (int i=0; i < newMachine.numberOfParts; i++) {
            machine.parts[machine.numberOfParts + i] = newMachine.parts[i];
            machine.parts[machine.numberOfParts + i].line = lineNumber;
        }
        machine.numberOfParts += newMachine.numberOfParts;
        lineNumber ++;

        free(lineCurrent);
    }

    int total = 0;
    for (int i=0; i < numberOfGearPositions; i++) {
        int mult = 1;
        int numberOfMult = 0;
        for (int j=0; j < machine.numberOfParts; j++) {
            if (machine.parts[j].line >= gearPositions[i].line - 1 && machine.parts[j].line <= gearPositions[i].line + 1) {
                if (
                    machine.parts[j].posStart + machine.parts[j].length >= gearPositions[i].index
                    && machine.parts[j].posStart <= gearPositions[i].index + 1
                ) {
                    mult *= machine.parts[j].partNumber;
                    numberOfMult += 1;
                }
            }
        }
        if (numberOfMult == 2) {
            total += mult;
        }
    }
    return total;
}
