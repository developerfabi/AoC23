//
// Created by Fabian Metzger on 04.12.23.
//
#include <stdbool.h>

#ifndef AOC23_LIB_H
#define AOC23_LIB_H

#define min(a, b) (((a) < (b)) ? (a) : (b))

bool isBlank(char input[]);
bool isPrime(int64_t number);
bool allZero(int64_t * numbers, int numberOfNumbers);

char *  readUntilCharacter(char input[], char breakpoint, int * offsetPointer, int defaultBufferSize);

typedef struct {
    char * buffer;
    size_t size;
    int index;
} CharBuffer;

int64_t parseInt(char * input);

CharBuffer createCharBuffer(int size);
bool writeToCharBuffer(char toWrite, CharBuffer * buffer);
void resetCharBuffer(CharBuffer * buffer);
bool charBufferHasContent(CharBuffer * buffer);
int64_t readIntAndResetCharBuffer(CharBuffer * buffer);
void releaseCharBuffer(CharBuffer * buffer);

int64_t * readNumbersWithBufferSize(char input[], int bufferSize, int * numberOfElements);
int64_t * readNumbers(char input[], int * numberOfElements);

#endif //AOC23_LIB_H
