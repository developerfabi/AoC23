//
// Created by Fabian Metzger on 04.12.23.
//
#include <stdbool.h>

#ifndef AOC23_LIB_H
#define AOC23_LIB_H

char *  readUntilCharacter(char input[], char breakpoint, int * offsetPointer, int defaultBufferSize);

typedef struct {
    char * buffer;
    size_t size;
    int index;
} CharBuffer;

CharBuffer createCharBuffer(int size);
bool writeToCharBuffer(char toWrite, CharBuffer * buffer);
void resetCharBuffer(CharBuffer * buffer);
bool charBufferHasContent(CharBuffer * buffer);

#endif //AOC23_LIB_H
