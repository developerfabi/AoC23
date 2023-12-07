//
// Created by Fabian Metzger on 04.12.23.
//

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "day_07.h"
#include "../lib.h"

#define MAX_CARD_VALUE 14

HandBid parseHandBid(char line[]) {
    int offset = 0;
    char * hand = readUntilCharacter(line, ' ', &offset, 5);
    char * bid = readUntilCharacter(line, ' ', &offset, 100);
    HandBid handBid = {
        hand,
        (int) parseInt(bid)
    };
    return handBid;
}

int getValueFromCard(char card) {
    return getValueFromCardWithJoker(card, 11);
}

int getValueFromCardWithJoker(char card, int jokerValue) {
    if (isdigit(card)) return (int) parseInt(&card);
    else if (card == 'A') return 14;
    else if (card == 'T') return 10;
    else if (card == 'J') return jokerValue;
    else if (card == 'Q') return 12;
    else if (card == 'K') return 13;
    return 0;
}

HandType getTypeFromHand(Hand hand) {
    int cardCount[MAX_CARD_VALUE+1] = {0};
    for (int i=0; i<5; i++) {
        cardCount[getValueFromCard(hand[i])] += 1;
    }

    int highestCount = 0;
    int secondHighestCount = 0;
    for (int i=0; i<=MAX_CARD_VALUE; i++) {
        if (cardCount[i] > highestCount) {
            secondHighestCount = highestCount;
            highestCount = cardCount[i];
        } else if (cardCount[i] > secondHighestCount) secondHighestCount = cardCount[i];
    }

    if (highestCount >= 5) return FIVE_OF_KIND;
    if (highestCount == 4) return FOUR_OF_KIND;
    if (highestCount == 3 && secondHighestCount == 2) return FULL_HOUSE;
    if (highestCount == 3) return THREE_OF_KIND;
    if (highestCount == 2 && secondHighestCount == 2) return TWO_PAIR;
    if (highestCount == 2) return ONE_PAIR;
    return HIGH_CARD;
}

HandType getTypeFromHandWithJoker(Hand hand, int jokerValue) {
    int cardCount[MAX_CARD_VALUE+1] = {0};
    for (int i=0; i<5; i++) {
        cardCount[getValueFromCardWithJoker(hand[i], jokerValue)] += 1;
    }

    int highestCount = 0;
    int secondHighestCount = 0;
    int jokerCount = cardCount[jokerValue];
    for (int i=0; i<=MAX_CARD_VALUE; i++) {
        if (i != jokerValue) {
            if (cardCount[i] > highestCount) {
                secondHighestCount = highestCount;
                highestCount = cardCount[i];
            } else if (cardCount[i] > secondHighestCount) secondHighestCount = cardCount[i];
        }
    }

    if ((highestCount+jokerCount) >= 5) return FIVE_OF_KIND;
    if ((highestCount+jokerCount) >= 4) return FOUR_OF_KIND;
    if (highestCount == 3 && secondHighestCount == 2) return FULL_HOUSE;
    if ((highestCount+jokerCount) >= 3 && secondHighestCount == 2) return FULL_HOUSE;
    if ((highestCount+jokerCount) >= 3) return THREE_OF_KIND;
    if (highestCount == 2 && secondHighestCount == 2) return TWO_PAIR;
    if ((highestCount+jokerCount) >= 2) return ONE_PAIR;
    return HIGH_CARD;
}

int compare(Hand first, Hand second) {
    HandType firstHandType = getTypeFromHand(first);
    HandType secondHandType = getTypeFromHand(second);
    if (firstHandType != secondHandType) return firstHandType > secondHandType;

    for (int i=0; i<5; i++) {
        int firstCardValue = getValueFromCard(first[i]);
        int secondCardValue = getValueFromCard(second[i]);
        if (firstCardValue != secondCardValue) return firstCardValue > secondCardValue;
    }

    return 0;
}

int compareWithJoker(Hand first, Hand second, int jokerValue) {
    HandType firstHandType = getTypeFromHandWithJoker(first, jokerValue);
    HandType secondHandType = getTypeFromHandWithJoker(second, jokerValue);
    if (firstHandType != secondHandType) return firstHandType > secondHandType;

    for (int i=0; i<5; i++) {
        int firstCardValue = getValueFromCardWithJoker(first[i], jokerValue);
        int secondCardValue = getValueFromCardWithJoker(second[i], jokerValue);
        if (firstCardValue != secondCardValue) return firstCardValue > secondCardValue;
    }

    return 0;
}

int64_t evaluateGame(char input[], bool withJoker) {
    size_t inputLength = strlen(input);

    HandBid * handBids = NULL;
    int numberOfHandBids = 0;

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);

        handBids = realloc(handBids, (numberOfHandBids+1)*sizeof(HandBid));
        handBids[numberOfHandBids] = parseHandBid(line);
        numberOfHandBids += 1;
    }

    if (handBids == NULL) return -1;

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i=0; i<(numberOfHandBids-1); i++) {
            if (
                !withJoker && compare(handBids[i].hand, handBids[i+1].hand)
                || withJoker && compareWithJoker(handBids[i].hand, handBids[i+1].hand, 1)
            ) {
                HandBid temp = handBids[i];
                handBids[i] = handBids[i+1];
                handBids[i+1] = temp;
                sorted = false;
            }
        }
    }

    int64_t total = 0;
    for (int i=0; i<numberOfHandBids; i++) {
        total += handBids[i].bid * (i+1);
        printf("%s / %d -> %d (Total: %llo)\n", handBids[i].hand, handBids[i].bid, handBids[i].bid * (i+1), total);
    }
    free(handBids);
    return total;
}

int64_t day7_1(char input[]) {
    return evaluateGame(input, false);
}

int64_t day7_2(char input[]) {
    return evaluateGame(input, true);
}
