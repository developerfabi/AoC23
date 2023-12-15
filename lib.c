//
// Created by Fabian Metzger on 04.12.23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lib.h"

Pattern parsePattern(char * input) {
    StringReader reader;
    initializeReader(&reader, input);

    Pattern pattern = {NULL, 0, -1};

    char * line;
    while ((line = readUntil(&reader, '\n'))) {
        int width = strlen(line);

        pattern.matrix = realloc(pattern.matrix, (pattern.height+1) * sizeof(char *));
        pattern.matrix[pattern.height] = line;
        pattern.height += 1;
        pattern.width = (pattern.width > width || pattern.width<0) ? width : pattern.width;
    }

    return pattern;
}

char * printPattern(Pattern pattern) {
    char * output = calloc((pattern.width+1) * pattern.height, sizeof(char));
    char * offsetPointer = output;
    for (int i=0; i<pattern.height; i++) {
        memcpy(offsetPointer, pattern.matrix[i], pattern.width);
        offsetPointer[pattern.width] = '/';
        offsetPointer += (pattern.width+1);
    }
    offsetPointer[0] = '\0';
    return output;
}

bool isBlank(char input[]) {
    size_t length = strlen(input);
    if (length <= 0) return true;
    for (int i=0; i<length; i++) {
        if (input[i] != ' ') return false;
    }
    return true;
}

bool isPrime(int64_t number) {
    if (number % 2 == 0) return false;
    for(int i=3; i * i <= number; i+=2){
        if(number%i==0) return false;
    }
    return true;
}

bool allZero(int64_t * numbers, int numberOfNumbers) {
    for (int i=0; i<numberOfNumbers; i++) {
        if (numbers[i] != 0) return false;
    }
    return true;
}

void initializeReader(StringReader * reader, char * input) {
    reader->length = strlen(input);
    reader->offset = 0;
    reader->string = input;
}

char * readUntil(StringReader * reader, char breakpoint) {
    if (reader->offset < reader->length) {
        return readUntilCharacter(reader->string, breakpoint, &reader->offset, 100);
    } else return NULL;
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

char * readUntilEmptyLine(char input[], int * offsetPointer, int defaultBufferSize) {
    size_t inputLength = strlen(input);

    size_t bufferSize = defaultBufferSize;
    char * lineBuffer = malloc(bufferSize+1);

    bool newlineAdjacent = false;

    int i = 0;
    while (i <= inputLength) {
        if (i >= bufferSize) {
            bufferSize = bufferSize * 2;
            lineBuffer = realloc(lineBuffer, bufferSize+1);
        }
        if (i >= inputLength || (newlineAdjacent && input[i+(*offsetPointer)] == '\n')) {
            lineBuffer[newlineAdjacent ? i-1 : i] = '\0';
            *offsetPointer += (i+1);
            return lineBuffer;
        } else {
            if (newlineAdjacent) lineBuffer[i-1] = '\n';
            if (input[i+(*offsetPointer)] == '\n') newlineAdjacent = true;
            else newlineAdjacent = false;
            lineBuffer[i] = input[i+(*offsetPointer)];
        }

        i ++;
    }

    lineBuffer[i] = '\0';
    *offsetPointer += (i+1);
    return lineBuffer;
}

int64_t parseInt(char * input) {
    char * succ;
    int64_t reading = strtoll(input, &succ, 10);
    return reading;
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
    int64_t reading = parseInt(buffer->buffer);

    resetCharBuffer(buffer);
    return reading;
}

void releaseCharBuffer(CharBuffer * buffer) {
    free(buffer->buffer);
}

int64_t * readNumbersWithBufferSize(char input[], int bufferSize, int * numberOfElements) {
    return readNumbersWithBufferSizeAndDelimiter(input, bufferSize, ' ', numberOfElements);
}

int64_t * readNumbersWithBufferSizeAndDelimiter(char input[], int bufferSize, char delimiter, int * numberOfElements) {
    size_t inputLength = strlen(input);
    CharBuffer buffer = createCharBuffer(32);

    int count = 0;

    int64_t * array = calloc(bufferSize, sizeof(int64_t));

    for (int i = 0; i <= inputLength; i++) {
        if (i >= inputLength || input[i] == delimiter) {
            if (charBufferHasContent(&buffer)) {
                while (count >= bufferSize) {
                    bufferSize *= 2;
                    array = realloc(array, bufferSize * sizeof(int64_t));
                }
                array[count] = readIntAndResetCharBuffer(&buffer);
                count += 1;
            }
        } else if (isdigit(input[i]) || input[i] == '-') {
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

int64_t * readNumbersWithDelimiter(char input[], char delimiter, int * numberOfElements) {
    return readNumbersWithBufferSizeAndDelimiter(input, 100, delimiter, numberOfElements);
}