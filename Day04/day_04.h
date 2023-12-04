//
// Created by Fabian Metzger on 04.12.23.
//

#ifndef AOC23_DAY_04_H
#define AOC23_DAY_04_H

typedef struct {
    int cardNumber;
    int numberOfWinningNumbers;
    int * winningNumbers;
    int nuberOfOwnNumbers;
    int * ownNumbers;
} Card;

typedef struct {
    Card card;
    int count;
} CardWithCopies;

Card parseCard(char line[]);
int getCardMatches(Card card);
int getCardPoints(Card card);

int day4_1(char input[]);
int day4_2(char input[]);

#endif //AOC23_DAY_04_H
