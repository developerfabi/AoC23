//
// Created by Fabian Metzger on 04.12.23.
//

#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "day_06.h"
#include "../lib.h"

Range getWinningRange(int64_t time, int64_t record) {
    double frac = ((double) time) / 2;
    double root = sqrt((pow((double) time, 2) / 4) - ((double) record));
    double lowerZero = frac - root;
    double upperZero = frac + root;
    Range range = {
        ceil(lowerZero),
        floor(upperZero)
    };
    if ((double) range.minimum <= lowerZero) range.minimum += 1;
    if ((double) range.maximum >= upperZero) range.maximum -= 1;
    return range;
}

int64_t day6_1(char input[]) {
    int offset = 0;
    char * lineTime = readUntilCharacter(input, '\n', &offset, 100);
    char * lineRecord = readUntilCharacter(input, '\n', &offset, 100);

    int numberOfRaces;

    int64_t * raceTime = readNumbers(lineTime, &numberOfRaces);
    int64_t * raceRecord = readNumbersWithBufferSize(lineRecord, numberOfRaces, NULL);

    int64_t winningCombinations = 1;
    for (int i=0; i < numberOfRaces; i++) {
        Range winningRange = getWinningRange(raceTime[i], raceRecord[i]);
        winningCombinations *= winningRange.maximum - winningRange.minimum + 1;
    }

    free(lineTime);
    free(lineRecord);
    free(raceTime);
    free(raceRecord);

    return winningCombinations;
}

int64_t day6_2(char input[]) {
    int offset = 0;
    char * lineTime = readUntilCharacter(input, '\n', &offset, 100);
    char * lineRecord = readUntilCharacter(input, '\n', &offset, 100);
    size_t lineTimeLength = strlen(lineTime);
    size_t lineRecordLength = strlen(lineRecord);

    CharBuffer buffer = createCharBuffer(32);
    for (int i = 0; i <= lineTimeLength; i++) {
        if (isdigit(lineTime[i])) writeToCharBuffer(lineTime[i], &buffer);
    }
    int64_t raceTime = readIntAndResetCharBuffer(&buffer);
    for (int i = 0; i <= lineRecordLength; i++) {
        if (isdigit(lineRecord[i])) writeToCharBuffer(lineRecord[i], &buffer);
    }
    int64_t raceRecord = readIntAndResetCharBuffer(&buffer);
    releaseCharBuffer(&buffer);

    free(lineTime);
    free(lineRecord);

    Range winningRange = getWinningRange(raceTime, raceRecord);
    return winningRange.maximum - winningRange.minimum + 1;
}
