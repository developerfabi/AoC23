//
// Created by Fabian Metzger on 04.12.23.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "day_05.h"
#include "../lib.h"

Mapping parseMapping(char input[], int * offsetPointer) {
    size_t inputLength = strlen(input);

    Mapping mapping;
    mapping.numberOfMappingRanges = 0;
    mapping.mappingRanges = NULL;

    while (*offsetPointer < inputLength) {
        char * line = readUntilCharacter(input, '\n', offsetPointer, 100);
        if (isBlank(line)) {
            return mapping;
        } else {
            size_t lineLength = strlen(line);

            MappingRange mappingRange = {-1,-1,-1};

            CharBuffer buffer = createCharBuffer(32);
            for (int i=0; i<=lineLength; i++) {
                if (i >= lineLength || line[i] == ' ') {
                    if (charBufferHasContent(&buffer)) {
                        int64_t number = readIntAndResetCharBuffer(&buffer);
                        if (mappingRange.destStart == -1) {
                            mappingRange.destStart = number;
                        } else if (mappingRange.sourceStart == -1) {
                            mappingRange.sourceStart = number;
                        } else if (mappingRange.length == -1) {
                            mappingRange.length = number;
                        }
                    }
                } else {
                    writeToCharBuffer(line[i], &buffer);
                }
            }
            releaseCharBuffer(&buffer);

            mapping.mappingRanges = realloc(mapping.mappingRanges, (mapping.numberOfMappingRanges + 1) * sizeof(MappingRange));
            mapping.mappingRanges[mapping.numberOfMappingRanges] = mappingRange;
            mapping.numberOfMappingRanges += 1;
        }
    }

    return mapping;
}

Almanac parseAlmanac(char input[]) {
    size_t inputLength = strlen(input);
    Almanac almanac;
    almanac.numberOfAvailableSeeds = 0;
    almanac.availableSeeds = NULL;
    int offset = 0;

    // Parse available seeds
    if (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        size_t lineLength = strlen(line);
        CharBuffer buffer = createCharBuffer(32);
        for (int i=7; i<=lineLength; i++) {
            if (i >= lineLength || line[i] == ' ') {
                if (charBufferHasContent(&buffer)) {
                    int64_t seed = readIntAndResetCharBuffer(&buffer);
                    almanac.availableSeeds = realloc(almanac.availableSeeds, (almanac.numberOfAvailableSeeds + 1) * sizeof(int64_t));
                    almanac.availableSeeds[almanac.numberOfAvailableSeeds] = seed;
                    almanac.numberOfAvailableSeeds += 1;
                }
            } else {
                writeToCharBuffer(line[i], &buffer);
            }
        }
    }

    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);

        if (strcmp(line, "seed-to-soil map:") == 0) almanac.seedToSoil = parseMapping(input, &offset);
        if (strcmp(line, "soil-to-fertilizer map:") == 0) almanac.soilToFertilizer = parseMapping(input, &offset);
        if (strcmp(line, "fertilizer-to-water map:") == 0) almanac.fertilizerToWater = parseMapping(input, &offset);
        if (strcmp(line, "water-to-light map:") == 0) almanac.waterToLight = parseMapping(input, &offset);
        if (strcmp(line, "light-to-temperature map:") == 0) almanac.lightToTemperature = parseMapping(input, &offset);
        if (strcmp(line, "temperature-to-humidity map:") == 0) almanac.temperatureToHumidity = parseMapping(input, &offset);
        if (strcmp(line, "humidity-to-location map:") == 0) almanac.humidityToLocation = parseMapping(input, &offset);
    }

    return almanac;
}

int64_t mapForward(int64_t from, Mapping mapping) {
    for (int i=0; i<mapping.numberOfMappingRanges; i++) {
        int64_t sourceStart = mapping.mappingRanges[i].sourceStart;
        if (from >= sourceStart && from < sourceStart + mapping.mappingRanges[i].length) {
            return mapping.mappingRanges[i].destStart + (from - sourceStart);
        }
    }
    return from;
}

int64_t mapForwardLeap(int64_t from, Mapping mapping, int64_t * noChangeFor) {
    int64_t nextChange = -1;
    for (int i=0; i<mapping.numberOfMappingRanges; i++) {
        int64_t sourceStart = mapping.mappingRanges[i].sourceStart;

        if (from >= sourceStart && from < sourceStart + mapping.mappingRanges[i].length) {
            int64_t startOffset = from - sourceStart;
            * noChangeFor = mapping.mappingRanges[i].length - startOffset;
            return mapping.mappingRanges[i].destStart + startOffset;
        } else if (from < sourceStart) {
            if (sourceStart < nextChange || nextChange == -1) nextChange = sourceStart;
        }
    }
    if (nextChange > from) * noChangeFor = nextChange - from;
    else * noChangeFor = -1;
    return from;
}

int64_t getLocationFromSeed(int64_t seed, Almanac almanac) {
    int64_t soil = mapForward(seed, almanac.seedToSoil);
    int64_t fertilizer = mapForward(soil, almanac.soilToFertilizer);
    int64_t water = mapForward(fertilizer, almanac.fertilizerToWater);
    int64_t light = mapForward(water, almanac.waterToLight);
    int64_t temperature = mapForward(light, almanac.lightToTemperature);
    int64_t humidity = mapForward(temperature, almanac.temperatureToHumidity);
    int64_t location = mapForward(humidity, almanac.humidityToLocation);
    printf(
        "%lld -> %lld -> %lld -> %lld -> %lld -> %lld -> %lld -> %lld\n",
        seed, soil, fertilizer, water, light, temperature, humidity, location
    );
    return location;
}

int64_t getLocationFromSeedLeap(int64_t seed, Almanac almanac, int64_t * noChangeFor) {
    int64_t nextChangeGlobal;
    int64_t nextChange;

    int64_t soil = mapForwardLeap(seed, almanac.seedToSoil, &nextChangeGlobal);

    int64_t fertilizer = mapForwardLeap(soil, almanac.soilToFertilizer, &nextChange);
    if ((nextChange > 0 && nextChange < nextChangeGlobal) || nextChangeGlobal == -1) nextChangeGlobal = nextChange;

    int64_t water = mapForwardLeap(fertilizer, almanac.fertilizerToWater, &nextChange);
    if ((nextChange > 0 && nextChange < nextChangeGlobal) || nextChangeGlobal == -1) nextChangeGlobal = nextChange;

    int64_t light = mapForwardLeap(water, almanac.waterToLight, &nextChange);
    if ((nextChange > 0 && nextChange < nextChangeGlobal) || nextChangeGlobal == -1) nextChangeGlobal = nextChange;

    int64_t temperature = mapForwardLeap(light, almanac.lightToTemperature, &nextChange);
    if ((nextChange > 0 && nextChange < nextChangeGlobal) || nextChangeGlobal == -1) nextChangeGlobal = nextChange;

    int64_t humidity = mapForwardLeap(temperature, almanac.temperatureToHumidity, &nextChange);
    if ((nextChange > 0 && nextChange < nextChangeGlobal) || nextChangeGlobal == -1) nextChangeGlobal = nextChange;

    int64_t location = mapForwardLeap(humidity, almanac.humidityToLocation, &nextChange);
    if ((nextChange > 0 && nextChange < nextChangeGlobal) || nextChangeGlobal == -1) nextChangeGlobal = nextChange;

    * noChangeFor = nextChangeGlobal;
    return location;
}

int64_t day5_1(char input[]) {
    Almanac almanac = parseAlmanac(input);
    int64_t lowest = -1;
    for (int i=0; i<almanac.numberOfAvailableSeeds; i++) {
        int64_t location = getLocationFromSeed(almanac.availableSeeds[i], almanac);
        printf("    => Seed %lld -> Location %lld\n", almanac.availableSeeds[i], location);
        if (location < lowest || lowest < 0) lowest = location;
    }
    return lowest;
}

int64_t day5_2(char input[]) {
    Almanac almanac = parseAlmanac(input);
    int64_t lowest = -1;
    for (int i=0; i<(almanac.numberOfAvailableSeeds - 1); i+=2) {

        for (int64_t j = almanac.availableSeeds[i]; j < (almanac.availableSeeds[i] + almanac.availableSeeds[i+1]); j++) {
            int64_t toNextChange = -1;
            int64_t location = getLocationFromSeedLeap(j, almanac, &toNextChange);

            if (location < lowest || lowest < 0) lowest = location;

            if (toNextChange > 1) {
                printf("(OG: %lld): Seed %lld -> Location %lld [Skipping to +%lld] \n", almanac.availableSeeds[i], j, location, toNextChange);
            } else {
                printf("(OG: %lld): Seed %lld -> Location %lld\n", almanac.availableSeeds[i], j, location);
            }
            if (toNextChange > 0) {
                j += toNextChange - 1;
            }
        }
    }
    return lowest;
}