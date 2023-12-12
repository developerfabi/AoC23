//
// Created by Fabian Metzger on 04.12.23.
//

#ifndef AOC23_DAY_10_H
#define AOC23_DAY_10_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    ABOVE, BELOW, LEFT, RIGHT
} Direction;

typedef enum {
    NONE, START, VERTICAL, HORIZONTAL, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST
} PipeType;

typedef struct {
    PipeType type;
    int mainLoopDistance; // -1 if not part of main loop
} Pipe;

typedef struct {
    int vertical;
    int horizontal;
} Position;

typedef struct {
    int width;
    int height;
    Pipe ** matrix;
    Position start;
} Maze;

PipeType parsePipeType(char symbol);
bool connectsTo(Direction direction, PipeType pipeType);

Maze parseMaze(char input[]);

Pipe getPipeAt(Position position, Maze maze);
Position * getMainLoopStartingDirections(Maze maze);
Position getNextPipe(Position currentPosition, Position prevPosition, Maze maze);

int64_t assignMainLoopDistance(Maze * maze);

int64_t day10_1(char input[]);
int64_t day10_2(char input[]);

#endif //AOC23_DAY_10_H
