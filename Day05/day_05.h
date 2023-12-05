//
// Created by Fabian Metzger on 04.12.23.
//

#ifndef AOC23_DAY_05_H
#define AOC23_DAY_05_H

typedef struct {
    int64_t sourceStart;
    int64_t destStart;
    int64_t length;
} MappingRange;

typedef struct {
    int numberOfMappingRanges;
    MappingRange * mappingRanges;
} Mapping;

typedef struct {
    int numberOfAvailableSeeds;
    int64_t * availableSeeds;
    Mapping seedToSoil;
    Mapping soilToFertilizer;
    Mapping fertilizerToWater;
    Mapping waterToLight;
    Mapping lightToTemperature;
    Mapping temperatureToHumidity;
    Mapping humidityToLocation;
} Almanac;

Almanac parseAlmanac(char input[]);

int64_t mapForward(int64_t from, Mapping mapping);
int64_t mapForwardLeap(int64_t from, Mapping mapping, int64_t * noChangeFor);
int64_t getLocationFromSeed(int64_t seed, Almanac almanac);
int64_t getLocationFromSeedLeap(int64_t seed, Almanac almanac, int64_t * noChangeFor);

int64_t day5_1(char input[]);
int64_t day5_2(char input[]);

#endif //AOC23_DAY_05_H
