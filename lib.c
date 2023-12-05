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

CharBuffer createCharBuffer(int size) {
    CharBuffer buffer;
    buffer.buffer = (char *) malloc((size+1) * sizeof(char));
    buffer.size = size;
    buffer.index = 0;
    memset(buffer.buffer, '\0', size+1);
    return buffer;
}

bool writeToCharBuffer(char toWrite, CharBuffer * buffer) {
    if (buffer->index < buffer->size) {
        buffer->buffer[buffer->index] = toWrite;
        buffer->index += 1;
        return true;
    }
    return false;
}

void resetCharBuffer(CharBuffer * buffer) {
    memset(buffer->buffer, '\0', buffer->size + 1);
    buffer->index = 0;
}

bool charBufferHasContent(CharBuffer * buffer) {
    return buffer->index > 0;
}