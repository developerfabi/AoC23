//
// Created by Fabian Metzger on 11.12.23.
//

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "day_15.h"
#include "../lib.h"

void insertLens(LensBoxCollection * lensBoxCollection, char * label, int focalLength) {
    LavaLens * newLens = malloc(sizeof(LavaLens));
    newLens->label = label;
    newLens->focalLength = focalLength;

    int64_t boxID = createHash(label);
    LavaLens * prevLens = lensBoxCollection->firstLens[boxID];
    if (prevLens == NULL) {
        lensBoxCollection->firstLens[boxID] = newLens;
    } else {
        while (strcmp(prevLens->label, label) != 0 && prevLens->nextLens != NULL) prevLens = prevLens->nextLens;
        if (strcmp(prevLens->label, label) == 0) {
            prevLens->focalLength = focalLength;
            free(newLens);
        } else {
            prevLens->nextLens = newLens;
        }
    }
    printf("Inserted in box %lld, focal %d (label %s)\n", boxID, focalLength, label);
}

void removeLens(LensBoxCollection * lensBoxCollection, char * label) {
    int64_t boxID = createHash(label);
    LavaLens * prevLens = lensBoxCollection->firstLens[boxID];
    if (prevLens == NULL) return;

    if (strcmp(prevLens->label, label) == 0) {
        LavaLens * subsequent = prevLens->nextLens;
        free(prevLens);
        lensBoxCollection->firstLens[boxID] = subsequent;
    } else {
        while (prevLens->nextLens != NULL && strcmp(prevLens->nextLens->label, label) != 0) prevLens = prevLens->nextLens;
        if (prevLens->nextLens != NULL && strcmp(prevLens->nextLens->label, label) == 0) {
            LavaLens * subsequent = prevLens->nextLens->nextLens;
            free(prevLens->nextLens);
            prevLens->nextLens = subsequent;
        }
    }
    printf("Removed from box %lld (label %s)\n", boxID, label);
}

void processInstruction(LensBoxCollection * lensBoxCollection, char * instruction) {
    int lengthOfLabel = 0;
    char * label = calloc(11, sizeof(char));
    bool add = false;
    int focalLength = 0;
    for (int i=0; i<strlen(instruction); i++) {
        if (instruction[i] != '\n') {
            if (instruction[i] == '=') {
                add = true;
            } else if (isdigit(instruction[i])) {
                focalLength = (int) parseInt(instruction+(i* sizeof(char)));
                i=INT32_MAX;
            } else if (instruction[i] != '-' && instruction[i] != '\n') {
                label[lengthOfLabel] = instruction[i];
                lengthOfLabel += 1;
            }
        }
    }
    label[lengthOfLabel] = '\0';

    if (add) {
        insertLens(lensBoxCollection, label, focalLength);
    } else {
        removeLens(lensBoxCollection, label);
    }
}

int64_t calculateFocalPower(LensBoxCollection lensBoxCollection) {
    int64_t total = 0;
    for (int i=0; i<256; i++) {
        int slot = 1;
        LavaLens * lens = lensBoxCollection.firstLens[i];
        while (lens != NULL) {
            printf("For box %d (%d), slot %d, focal %d (label %s), adding: %d\n", i, i+1, slot, lens->focalLength, lens->label, (i+1) * slot * lens->focalLength);
            total += (i+1) * slot * lens->focalLength;
            lens = lens->nextLens;
            slot ++;
        }
    }
    return total;
}

int64_t createHash(char input[]) {
    int64_t currentValue = 0;
    for (int i=0; i<strlen(input); i++) {
        if (input[i] != '\n') {
            currentValue += (int) input[i];
            currentValue *= 17;
            currentValue = currentValue % 256;
        }
    }
    return currentValue;
}

int64_t day15_1(char input[]) {
    StringReader reader;
    initializeReader(&reader, input);

    int64_t total = 0;
    char * instruction;
    while ((instruction = readUntil(&reader, ','))) {
        total += createHash(instruction);
    }
    return total;
}

int64_t day15_2(char input[]) {
    StringReader reader;
    initializeReader(&reader, input);

    LensBoxCollection lensBoxCollection = {calloc(256, sizeof(LavaLens *))};

    char * instruction;
    while ((instruction = readUntil(&reader, ','))) {
        processInstruction(&lensBoxCollection, instruction);
    }

    printf("-----\n");
    return calculateFocalPower(lensBoxCollection);
}
