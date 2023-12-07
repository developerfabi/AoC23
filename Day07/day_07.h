//
// Created by Fabian Metzger on 04.12.23.
//

#include <stdbool.h>

#ifndef AOC23_DAY_07_H
#define AOC23_DAY_07_H

typedef enum {
    FIVE_OF_KIND = 7,
    FOUR_OF_KIND = 6,
    FULL_HOUSE = 4,
    THREE_OF_KIND = 3,
    TWO_PAIR = 2,
    ONE_PAIR = 1,
    HIGH_CARD = 0
} HandType;

typedef char * Hand;

typedef struct {
    Hand hand;
    int bid;
} HandBid;

HandBid parseHandBid(char line[]);

int getValueFromCard(char card);
int getValueFromCardWithJoker(char card, int jokerValue);
HandType getTypeFromHand(Hand hand);
HandType getTypeFromHandWithJoker(Hand hand, int jokerValue);

int compare(Hand first, Hand second);
int compareWithJoker(Hand first, Hand second, int jokerValue);

int64_t evaluateGame(char input[], bool withJoker);

int64_t day7_1(char input[]);
int64_t day7_2(char input[]);

#endif //AOC23_DAY_07_H
