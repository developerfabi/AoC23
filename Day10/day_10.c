//
// Created by Fabian Metzger on 04.12.23.
//

#include <string.h>
#include <stdlib.h>
#include "day_10.h"
#include "../lib.h"

PipeType parsePipeType(char symbol) {
    if (symbol == '|') return VERTICAL;
    if (symbol == '-') return HORIZONTAL;
    if (symbol == 'L') return NORTH_EAST;
    if (symbol == 'J') return NORTH_WEST;
    if (symbol == '7') return SOUTH_WEST;
    if (symbol == 'F') return SOUTH_EAST;
    if (symbol == 'S') return START;
    return NONE;
}

bool connectsTo(Direction direction, PipeType pipeType) {
    if (direction == ABOVE) return pipeType==VERTICAL || pipeType==NORTH_EAST || pipeType==NORTH_WEST;
    if (direction == BELOW) return pipeType==VERTICAL || pipeType==SOUTH_EAST || pipeType==SOUTH_WEST;
    if (direction == LEFT) return pipeType==HORIZONTAL || pipeType==NORTH_WEST || pipeType==SOUTH_WEST;
    if (direction == RIGHT) return pipeType==HORIZONTAL || pipeType==NORTH_EAST || pipeType==SOUTH_EAST;
    return false;
}

Maze parseMaze(char input[]) {
    size_t inputLength = strlen(input);

    Maze maze = {-1, 0, NULL, {-1, -1}};

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        int width = strlen(line);
        maze.matrix = realloc(maze.matrix, (maze.height+1) * sizeof(Pipe *));
        maze.matrix[maze.height] = calloc(width, sizeof(Pipe));

        for (int i=0; i<width; i++) {
            maze.matrix[maze.height][i].type = parsePipeType(line[i]);
            maze.matrix[maze.height][i].mainLoopDistance = -1;
            if (maze.matrix[maze.height][i].type == START) {
                maze.start.vertical = maze.height;
                maze.start.horizontal = i;
            }
        }

        maze.height += 1;
        maze.width = (maze.width > width || maze.width==-1) ? width : maze.width;
    }

    return maze;
}

Pipe getPipeAt(Position position, Maze maze) {
    return maze.matrix[position.vertical][position.horizontal];
}

Position * getMainLoopStartingDirections(Maze maze) {
    Position firstNeighbour = {-1, -1};
    Position secondNeighbour = {-1, -1};

    if (maze.start.vertical > 0) {
        Pipe above = maze.matrix[maze.start.vertical-1][maze.start.horizontal];
        if (connectsTo(BELOW, above.type)) {
            Position * toAssign = firstNeighbour.vertical==-1 ? &firstNeighbour : &secondNeighbour;
            toAssign->vertical = maze.start.vertical-1;
            toAssign->horizontal = maze.start.horizontal;
        }
    }

    if (maze.start.vertical < maze.height-1) {
        Pipe below = maze.matrix[maze.start.vertical+1][maze.start.horizontal];
        if (connectsTo(ABOVE, below.type)) {
            Position * toAssign = firstNeighbour.vertical==-1 ? &firstNeighbour : &secondNeighbour;
            toAssign->vertical = maze.start.vertical+1;
            toAssign->horizontal = maze.start.horizontal;
        }
    }

    if (maze.start.horizontal > 0) {
        Pipe left = maze.matrix[maze.start.vertical][maze.start.horizontal-1];
        if (connectsTo(RIGHT, left.type)) {
            Position * toAssign = firstNeighbour.vertical==-1 ? &firstNeighbour : &secondNeighbour;
            toAssign->vertical = maze.start.vertical;
            toAssign->horizontal = maze.start.horizontal-1;
        }
    }

    if (maze.start.horizontal < maze.width-1) {
        Pipe right = maze.matrix[maze.start.vertical][maze.start.horizontal+1];
        if (connectsTo(LEFT, right.type)) {
            Position * toAssign = firstNeighbour.vertical==-1 ? &firstNeighbour : &secondNeighbour;
            toAssign->vertical = maze.start.vertical;
            toAssign->horizontal = maze.start.horizontal+1;
        }
    }

    Position * pos = calloc(2, sizeof(Position));
    pos[0] = firstNeighbour;
    pos[1] = secondNeighbour;
    return pos;
}

Position getNextPipe(Position currentPosition, Position prevPosition, Maze maze) {
    PipeType type = getPipeAt(currentPosition, maze).type;
    Position offset = {
        (currentPosition.vertical - prevPosition.vertical),
        (currentPosition.horizontal - prevPosition.horizontal),
    };
    if (type==VERTICAL) {
        Position finalPosition = {
            (currentPosition.vertical + offset.vertical), prevPosition.horizontal
        }; return finalPosition;
    }
    if (type==HORIZONTAL) {
        Position finalPosition = {
            prevPosition.vertical, (currentPosition.horizontal + offset.horizontal)
        }; return finalPosition;
    }
    if (type==NORTH_EAST || type==SOUTH_WEST) {
        Position finalPosition = {
                (currentPosition.vertical + offset.horizontal),
                (currentPosition.horizontal + offset.vertical)
        }; return finalPosition;
    }
    if (type==NORTH_WEST || type==SOUTH_EAST) {
        Position finalPosition = {
                (currentPosition.vertical - offset.horizontal),
                (currentPosition.horizontal - offset.vertical)
        }; return finalPosition;
    }
    Position finalPosition = {currentPosition.vertical, currentPosition.horizontal};
    return finalPosition;
}

int64_t assignMainLoopDistance(Maze * maze) {
    Position * pastPositions = calloc(2, sizeof(Position));
    pastPositions[0] = maze->start;
    pastPositions[1] = maze->start;
    Position * positions = getMainLoopStartingDirections(*maze);

    int distance = 1;
    while (getPipeAt(positions[0], *maze).mainLoopDistance == -1 && getPipeAt(positions[1], *maze).mainLoopDistance == -1) {
        maze->matrix[positions[0].vertical][positions[0].horizontal].mainLoopDistance = distance;
        maze->matrix[positions[1].vertical][positions[1].horizontal].mainLoopDistance = distance;
        Position nextPosition0 = getNextPipe(positions[0], pastPositions[0], *maze);
        Position nextPosition1 = getNextPipe(positions[1], pastPositions[1], *maze);
        pastPositions[0] = positions[0];
        pastPositions[1] = positions[1];
        positions[0] = nextPosition0;
        positions[1] = nextPosition1;
        distance += 1;
    }
    return distance-1;
}

int64_t day10_1(char input[]) {
    Maze maze = parseMaze(input);
    return assignMainLoopDistance(&maze);
}

int64_t day10_2(char input[]) {
    return -1;
}
