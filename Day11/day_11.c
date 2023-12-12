//
// Created by Fabian Metzger on 11.12.23.
//

#include <string.h>
#include <stdlib.h>
#include "day_11.h"
#include "../lib.h"

Universe parseUniverse(char input[]) {
    size_t inputLength = strlen(input);

    Universe universe = {NULL, 0, 0, -1, NULL, NULL, 0, 0};

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        int width = strlen(line);


        for (int i=0; i<width; i++) {
            if (line[i] == '#') {
                universe.galaxies = realloc(universe.galaxies, (universe.numberOfGalaxies+1) * sizeof(Galaxy));
                universe.galaxies[universe.numberOfGalaxies].posVertical = universe.height;
                universe.galaxies[universe.numberOfGalaxies].posHorizontal = i;
                universe.numberOfGalaxies += 1;
            }
        }

        universe.height += 1;
        universe.width = (universe.width > width || universe.width==-1) ? width : universe.width;
    }

    return universe;
}

void calculateEmptySpace(Universe * universe) {
    int *lines = calloc(universe->height, sizeof(int));
    int *columns = calloc(universe->width, sizeof(int));

    universe->numberOfEmptyLines = universe->height;
    universe->numberOfEmptyColumns = universe->width;
    for (int i = 0; i < universe->numberOfGalaxies; i++) {
        if (lines[universe->galaxies[i].posVertical] == 0) {
            lines[universe->galaxies[i].posVertical] = 1;
            universe->numberOfEmptyLines -= 1;
        }
        if (columns[universe->galaxies[i].posHorizontal] == 0) {
            columns[universe->galaxies[i].posHorizontal] = 1;
            universe->numberOfEmptyColumns -= 1;
        }
    }

    universe->emptyLines = calloc(universe->numberOfEmptyLines, sizeof(int));
    universe->emptyColumns = calloc(universe->numberOfEmptyColumns, sizeof(int));

    int countLines = 0;
    for (int i = 0; i < universe->height; i++) {
        if (lines[i] == 0) {
            universe->emptyLines[countLines] = i;
            countLines += 1;
        }
    }

    int countColumns = 0;
    for (int i = 0; i < universe->width; i++) {
        if (columns[i] == 0) {
            universe->emptyColumns[countColumns] = i;
            countColumns += 1;
        }
    }

    free(lines);
    free(columns);
}

int64_t calculateDistance(Galaxy first, Galaxy second, Universe universe, int expansion) {
    int64_t distance = abs(first.posVertical - second.posVertical) + abs(first.posHorizontal - second.posHorizontal);

    int minPosVertical = min(first.posVertical, second.posVertical);
    int maxPosVertical = max(first.posVertical, second.posVertical);
    for (int i=0; i<universe.numberOfEmptyLines; i++) {
        if (universe.emptyLines[i] > minPosVertical && universe.emptyLines[i] < maxPosVertical) distance += expansion - 1;
    }

    int minPosHorizontal = min(first.posHorizontal, second.posHorizontal);
    int maxPosHorizontal = max(first.posHorizontal, second.posHorizontal);
    for (int i=0; i<universe.numberOfEmptyColumns; i++) {
        if (universe.emptyColumns[i] > minPosHorizontal && universe.emptyColumns[i] < maxPosHorizontal) distance += expansion - 1;
    }

    return distance;
}

int64_t day11_1(char input[]) {
    Universe universe = parseUniverse(input);
    calculateEmptySpace(&universe);

    int64_t totalCountOfDistance = 0;
    for (int i=0; i<universe.numberOfGalaxies; i++) {
        for (int j=i+1; j<universe.numberOfGalaxies; j++) {
            totalCountOfDistance += calculateDistance(universe.galaxies[i], universe.galaxies[j], universe, 2);
        }
    }
    return totalCountOfDistance;
}

int64_t day11_2(char input[]) {
    Universe universe = parseUniverse(input);
    calculateEmptySpace(&universe);

    int64_t totalCountOfDistance = 0;
    for (int i=0; i<universe.numberOfGalaxies; i++) {
        for (int j=i+1; j<universe.numberOfGalaxies; j++) {
            totalCountOfDistance += calculateDistance(universe.galaxies[i], universe.galaxies[j], universe, 1000000);
        }
    }
    return totalCountOfDistance;
}
