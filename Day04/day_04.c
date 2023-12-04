//
// Created by Fabian Metzger on 04.12.23.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "../lib.h"
#include "day_04.h"

Card parseCard(char line[]) {
    size_t inputLength = strlen(line);
    int offset = 5;

    Card card;
    char * cardNumber = readUntilCharacter(line, ':', &offset, 10);
    card.cardNumber = atoi(cardNumber);
    card.numberOfWinningNumbers = 0;
    card.nuberOfOwnNumbers = 0;
    card.winningNumbers = NULL;
    card.ownNumbers = NULL;

    CharBuffer numberBuffer = createCharBuffer(10);

    bool readingWinningNumbers = true;

    offset += 1;
    while (offset <= inputLength) {
        if (offset >= inputLength || line[offset] == ' ') {
            if (charBufferHasContent(&numberBuffer)) {
                int number = atoi(numberBuffer.buffer);

                if (readingWinningNumbers) {
                    card.winningNumbers = realloc(card.winningNumbers, (card.numberOfWinningNumbers + 1) * sizeof(int));
                    card.winningNumbers[card.numberOfWinningNumbers] = number;
                    card.numberOfWinningNumbers += 1;
                } else {
                    card.ownNumbers = realloc(card.ownNumbers, (card.nuberOfOwnNumbers + 1) * sizeof(int));
                    card.ownNumbers[card.nuberOfOwnNumbers] = number;
                    card.nuberOfOwnNumbers += 1;
                }

                resetCharBuffer(&numberBuffer);
            }
        } else if (line[offset] == '|') {
            readingWinningNumbers = false;
        } else if (isdigit(line[offset])) {
            writeToCharBuffer(line[offset], &numberBuffer);
        }
        offset ++;
    }

    return card;
}

int getCardMatches(Card card) {
    int count = 0;
    printf("Card %d: ", card.cardNumber);
    for (int i=0; i < card.nuberOfOwnNumbers; i++) {
        for (int j=0; j < card.numberOfWinningNumbers; j++) {
            if (card.ownNumbers[i] == card.winningNumbers[j]) {
                count += 1;
                printf("%d, ", card.ownNumbers[i]);
                j = card.numberOfWinningNumbers; // End loop
            }
        }
    }
    printf("\n");
    return count;
}

int getCardPoints(Card card) {
    int count = getCardMatches(card);
    if (count > 0) return (1 << (count - 1)); // = 2^count
    else return 0;
}

int day4_1(char input[]) {
    size_t inputLength = strlen(input);
    int total = 0;

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        Card card = parseCard(line);
        free(line);

        total += getCardPoints(card);
    }

    return total;
}

int day4_2(char input[]) {
    size_t inputLength = strlen(input);

    int numberOfUniqueCards = 0;
    CardWithCopies * uniqueCards = NULL;

    int offset = 0;
    while (offset < inputLength) {
        char * line = readUntilCharacter(input, '\n', &offset, 100);
        Card card = parseCard(line);
        free(line);

        uniqueCards = realloc(uniqueCards, (numberOfUniqueCards + 1) * sizeof(CardWithCopies));
        uniqueCards[numberOfUniqueCards].card = card;
        uniqueCards[numberOfUniqueCards].count = 1;
        numberOfUniqueCards += 1;
    }

    int total = 0;
    for (int i=0; i < numberOfUniqueCards; i++) {
        int matches = getCardMatches(uniqueCards[i].card);
        for (int j=i+1; j<=i+matches && j<numberOfUniqueCards; j++) {
            printf("Adding %d copies to card %d\n", uniqueCards[i].count, uniqueCards[j].card.cardNumber);
            uniqueCards[j].count += uniqueCards[i].count;
        }
        total += uniqueCards[i].count;
    }
    return total;
}