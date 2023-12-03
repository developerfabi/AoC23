#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "day_01.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

int day1_1(char input[]) {
    size_t inputLength = strlen(input);

    int total = 0;
    char first = -1;
    char last = -1;
    for (int i=0; i<=inputLength; i++) {
        if (i >= inputLength || input[i] == '\n') {
            char number[] = "00";
            number[0] = first;
            number[1] = last;
            total += atoi(number);
            first = -1;
            last = -1;
        } else if (isdigit(input[i])) {
            if (first == -1) { first = input[i]; }
            last = input[i];
        }
    }

    return total;
}

int day1_2(char input[]) {
    int inputLength = strlen(input);

    int total = 0;
    char first = -1;
    char last = -1;
    char * numberText = (char *) malloc(6 * sizeof(char));
    memset(numberText, '\0', 6);

    for (int i=0; i<=inputLength; i++) {
        if (i >= inputLength || input[i] == '\n') {
            char number[] = "00";
            number[0] = first;
            number[1] = last;
            total += atoi(number);
            printf("%d -> %d\n", atoi(number), total);
            first = -1;
            last = -1;
            memset(numberText, '\0', 6);
        } else if (isdigit(input[i])) {
            if (first == -1) { first = input[i]; }
            last = input[i];
            memset(numberText, '\0', 6);
        } else {
            int currentTextLength = strlen(numberText);
            if (currentTextLength >= 5) {
                for (int j=0; j<(currentTextLength-1); j++) {
                    numberText[j] = numberText[j+1];
                }
            }
            numberText[min(4, currentTextLength)] = input[i];
            int foundInt = searchForDigit(numberText);
            if (foundInt >= 0) {
                if (first == -1) { first = foundInt + '0'; }
                last = foundInt + '0';
            }
        }
    }

    free(numberText);
    return total;
}

int searchForDigit(char text[]) {
    if (strstr(text, "zero") != NULL) return 0;
    if (strstr(text, "one") != NULL) return 1;
    if (strstr(text, "two") != NULL) return 2;
    if (strstr(text, "three") != NULL) return 3;
    if (strstr(text, "four") != NULL) return 4;
    if (strstr(text, "five") != NULL) return 5;
    if (strstr(text, "six") != NULL) return 6;
    if (strstr(text, "seven") != NULL) return 7;
    if (strstr(text, "eight") != NULL) return 8;
    if (strstr(text, "nine") != NULL) return 9;
    return -1;
}