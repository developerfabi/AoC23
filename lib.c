//
// Created by Fabian Metzger on 04.12.23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

char * readUntilCharacter(char input[], char breakpoint, int * offsetPointer, int defaultBufferSize) {
    size_t inputLength = strlen(input);

    size_t bufferSize = defaultBufferSize;
    char * lineBuffer = malloc(bufferSize+1);

    int i = 0;
    while (i <= inputLength) {
        if (i >= bufferSize) {
            bufferSize = bufferSize * 2;

            lineBuffer = realloc(lineBuffer, bufferSize+1);
        }
        if (i >= inputLength || input[i+(*offsetPointer)] == breakpoint) {
            lineBuffer[i] = '\0';
            *offsetPointer += (i+1);
            return lineBuffer;
        } else {
            lineBuffer[i] = input[i+(*offsetPointer)];
        }

        i ++;
    }

    lineBuffer[i] = '\0';
    *offsetPointer += (i+1);
    return lineBuffer;
}