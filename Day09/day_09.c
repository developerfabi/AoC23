//
// Created by Fabian Metzger on 04.12.23.
//

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "day_09.h"
#include "../lib.h"

int64_t extrapolate(int64_t * sequence, int numberOfSequenceItems, bool backwards) {
    int64_t ** layers = malloc(sizeof(int64_t *));
    layers[0] = sequence;
    int numberOfLayers = 1;
    while (!allZero(layers[numberOfLayers - 1], numberOfSequenceItems - numberOfLayers + 1)) {
        layers = realloc(layers, (numberOfLayers+1) * sizeof(int64_t *));
        layers[numberOfLayers] = calloc(numberOfSequenceItems-numberOfLayers, sizeof(int64_t));
        for (int i=0; i<numberOfSequenceItems-numberOfLayers; i++) {
            layers[numberOfLayers][i] = layers[numberOfLayers-1][i+1] - layers[numberOfLayers-1][i];
        }
        numberOfLayers += 1;
    }

    int64_t total = 0;
    bool positive = true;
    for (int i=0; i<(numberOfLayers-1); i++) {
        int64_t value = layers[i][backwards ? 0 : numberOfSequenceItems-i-1];
        printf("%lld +/- ", value);
        if (backwards && !positive) {
            total -= value;
            positive = !positive;
        } else {
            total += value;
            positive = !positive;
        }
    }
    printf("0 = %lld\n", total);

    free(layers);
    return total;
}

int64_t day9_1(char input[]) { // 820847869
    size_t inputLength = strlen(input);

    int64_t total = 0;

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        int numberOfSequenceItems;
        int64_t * sequence = readNumbers(line, &numberOfSequenceItems);
        total += extrapolate(sequence, numberOfSequenceItems, false);
    }

    return total;
}

int64_t day9_2(char input[]) {
    size_t inputLength = strlen(input);

    int64_t total = 0;

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        int numberOfSequenceItems;
        int64_t * sequence = readNumbers(line, &numberOfSequenceItems);
        total += extrapolate(sequence, numberOfSequenceItems, true);
    }

    return total;
}
