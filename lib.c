//
// Created by Fabian Metzger on 04.12.23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lib.h"

bool isBlank(char input[]) {
    size_t length = strlen(input);
    if (length <= 0) return true;
    for (int i=0; i<length; i++) {
        if (input[i] != ' ') return false;
    }
    return true;
}

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

int64_t readIntAndResetCharBuffer(CharBuffer * buffer) {
    char * succ;
    int64_t reading = strtoll(buffer->buffer, &succ, 10);

    resetCharBuffer(buffer);
    return reading;
}

void releaseCharBuffer(CharBuffer * buffer) {
    free(buffer->buffer);
}

int64_t * readNumbersWithBufferSize(char input[], int bufferSize, int * numberOfElements) {
    size_t inputLength = strlen(input);
    CharBuffer buffer = createCharBuffer(32);

    int count = 0;

    int64_t * array = calloc(bufferSize, sizeof(int64_t));

    for (int i = 0; i <= inputLength; i++) {
        if (i >= inputLength || input[i] == ' ') {
            if (charBufferHasContent(&buffer)) {
                while (count >= bufferSize) {
                    bufferSize *= 2;
                    array = realloc(array, bufferSize * sizeof(int64_t));
                }
                array[count] = readIntAndResetCharBuffer(&buffer);
                count += 1;
            }
        } else if (isdigit(input[i])) {
            writeToCharBuffer(input[i], &buffer);
        }
    }

    releaseCharBuffer(&buffer);
    array = realloc(array, count * sizeof(int64_t));

    if (numberOfElements != NULL) {
        *numberOfElements = count;
    }
    return array;
}

int64_t * readNumbers(char input[], int * numberOfElements) {
    return readNumbersWithBufferSize(input, 100, numberOfElements);
}