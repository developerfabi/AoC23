//
// Created by Fabian Metzger on 04.12.23.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "../lib.h"
#include "day_08.h"

Route parseRoute(char input[]) {
    size_t inputLength = strlen(input);

    int offset = 0;
    char * directionsString = readUntilCharacter(input, '\n', &offset, 100);
    Directions directions = {directionsString};

    WayInstruction * wayInstructions = NULL;
    int numberOfWayInstructions = 0;

    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        size_t lineLength = strlen(line);
        if (lineLength > 0) {
            int lineOffset = 0;
            char * instruction = readUntilCharacter(line, ' ', &lineOffset, 20);
            lineOffset += 3;
            char * left = readUntilCharacter(line, ',', &lineOffset, 20);
            lineOffset += 1;
            char * right = readUntilCharacter(line, ')', &lineOffset, 20);

            wayInstructions = realloc(wayInstructions, (numberOfWayInstructions+1)*sizeof(WayInstruction));
            WayInstruction newWayInstruction = {instruction, left, right};
            wayInstructions[numberOfWayInstructions] = newWayInstruction;
            numberOfWayInstructions += 1;
        }
    }

    Route route = {directions, wayInstructions, numberOfWayInstructions};
    return route;
}

bool getDirection(Directions directions, int64_t i) {
    const size_t directionLength = strlen(directions.direction);
    return directions.direction[i % directionLength] == 'R';
}

bool allWaypointsAtDest(char ** waypoints, int numberOfWaypoints) {
    for (int i=0; i<numberOfWaypoints; i++) {
        if (waypoints[i][2] != 'Z') return false;
    }
    return true;
}

bool isCommonMultiple(int64_t common, int * numbers, int numberOfNumbers) {
    for (int i=0; i<numberOfNumbers; i++) {
        if (common % numbers[i] != 0) return false;
    }
    return true;
}

int64_t day8_1(char input[]) {
    Route route = parseRoute(input);

    int64_t i = 0;
    char * currentWaypoint = "AAA";
    while (strcmp(currentWaypoint, "ZZZ") != 0) {
        printf("%s\n", currentWaypoint);
        WayInstruction instruction;
        for (int j=0; j<route.numberOfWayInstructions; j++) {
            if (strcmp(currentWaypoint, route.wayInstructions[j].wayPoint) == 0) {
                instruction = route.wayInstructions[j];
            }
        }
        currentWaypoint = getDirection(route.directions, i) ? instruction.right : instruction.left;
        i++;
    }

    free(route.wayInstructions);
    return i;
}

int64_t day8_2(char input[]) {
    Route route = parseRoute(input);

    int64_t * cycleLength = calloc(1, sizeof(int64_t));
    int numberOfCycleLengths = 0;
    for (int i=0; i<route.numberOfWayInstructions; i++) {
        if (route.wayInstructions[i].wayPoint[2] == 'A') {
            int64_t steps = 0;
            char * currentWaypoint = route.wayInstructions[i].wayPoint;
            while (currentWaypoint[2] != 'Z') {
                WayInstruction instruction;
                for (int j=0; j<route.numberOfWayInstructions; j++) {
                    if (strcmp(currentWaypoint, route.wayInstructions[j].wayPoint) == 0) {
                        instruction = route.wayInstructions[j];
                    }
                }
                currentWaypoint = getDirection(route.directions, steps) ? instruction.right : instruction.left;
                steps++;
            }

            cycleLength = realloc(cycleLength, (numberOfCycleLengths+1)*sizeof(int64_t));
            cycleLength[numberOfCycleLengths] = steps;
            numberOfCycleLengths += 1;
        }
    }

//    int * cycleLengthRemainder = calloc(numberOfCycleLengths, sizeof(int));
//    memcpy(cycleLengthRemainder, cycleLength, numberOfCycleLengths * sizeof(int));
//    int primeBufferSize = 100;
//    int64_t * primes = calloc(primeBufferSize, sizeof(int64_t));
//    int64_t * biggest = calloc(primeBufferSize, sizeof(int64_t));
//    int numberOfPrimes = 0;
//    while (!allZero((int64_t *) cycleLengthRemainder, numberOfCycleLengths)) {
//        if (numberOfPrimes < 1) primes[0] = 2;
//        else if (numberOfPrimes < 2) primes[1] = 3;
//        else {
//            int64_t nextPrime = primes[numberOfPrimes-1] + 2;
//            while (!isPrime(nextPrime)) nextPrime += 2;
//            if (numberOfPrimes >= primeBufferSize) {
//                primeBufferSize *= 2;
//                primes = realloc(primes, primeBufferSize * sizeof(int64_t));
//                biggest = realloc(biggest, primeBufferSize * sizeof(int64_t));
//            }
//            primes[numberOfPrimes] = nextPrime;
//        }
//        numberOfPrimes += 1;
//
//        for (int i=0; i<numberOfCycleLengths; i++) {
//            int power = 0;
//            while (cycleLengthRemainder[i] % primes[numberOfPrimes-1] == 0) {
//                cycleLengthRemainder[i] = cycleLengthRemainder[i] / (int) primes[numberOfPrimes-1];
//                power += 1;
//            }
//            if (power > biggest[i]) biggest[i] = power;
//        }
//    }

//    int64_t common = cycleLength[0];
//    for (int i=0; i<numberOfPrimes; i++) {
//        common += primes[i] * biggest[i];
//    }

    int64_t common = 1;
    for (int i=0; i<numberOfCycleLengths; i++) {
        int64_t testingCommon = common * cycleLength[i];
        int64_t newCommon = testingCommon;
        while (testingCommon > common && testingCommon > cycleLength[i]) {
            testingCommon -= (common > cycleLength[i] ? common : cycleLength[i]);
            if (testingCommon % common == 0 && testingCommon % cycleLength[i] == 0) {
                newCommon = testingCommon;
            }
        }
        common = newCommon;
    }

//    free(primes);
//    free(biggest);
    free(cycleLength);
    //free(cycleLengthRemainder);
    free(route.wayInstructions);
    return common;
}
