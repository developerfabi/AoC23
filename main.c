//
// Created by Fabian Metzger on 03.12.23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "Day01/day_01.h"
#include "Day02/day_02.h"
#include "Day03/day_03.h"

int doTask(int day, int task, char input[]) {
    if (day == 1 && task == 1) return day1_1(input);
    if (day == 1 && task == 2) return day1_2(input);
    if (day == 2 && task == 1) return day2_1(input);
    if (day == 2 && task == 2) return day2_2(input);
    if (day == 3 && task == 1) return day3_1(input);
    if (day == 3 && task == 2) return day3_2(input);
    printf("No function found for day %d, task %d", day, task);
    exit(-1);
}

int main(int argc, char * argv[]) {

    if (argc != 3 && argc != 4) {
        printf("Expected two or three arguments (got %d): {Day} {Task} [Testfile]", (argc -1));
        return -1;
    }

    int day = atoi(argv[1]);
    int task = atoi(argv[2]);

    printf("Running AoC Day %d, Task %d\n", day, task);

    if (day < 1 || day > 24 || task < 1) {
        printf("Day has to be between 1 and 24 (inclusive). Task has to be 1 or above.\n");
        return -1;
    }

    char dayString[3];
    if (day < 10) sprintf(dayString, "0%d", day);
    else sprintf(dayString, "%d", day);

    char path[40];
    if (argc == 4) {
        sprintf(path, "./../Day%s/day_%s_input_%s.txt", dayString, dayString, argv[3]);
    } else {
        sprintf(path, "./../Day%s/day_%s_input.txt", dayString, dayString);
    }
    FILE * fp = fopen(path, "r");
    if (fp == NULL) {
        printf("No input file found (%s)\n", path);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char * input = malloc(filesize + 1);
    fread(input, filesize, 1, fp);
    fclose(fp);
    input[filesize] = '\0';

    int result = doTask(day, task, input);
    printf("-> Result: %d\n", result);
    return 0;
}
