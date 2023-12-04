#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SEQUENCE_LENGTH 10

void printRules() {
    printf("Welcome to the 'One-Armed Bandit' game!\n");
    printf("Game Rules:\n");
    printf("- You have a certain number of coins.\n");
    printf("- You place a bet and enter the length of the sequence of numbers.\n");
    printf("- If the sequence contains at least one 7, you win your bet back.\n");
    printf("- If all numbers in the sequence are the same, you win more.\n");
    printf("- If at least one-third of the numbers are the same, you win your bet back.\n");
    printf("Wins:\n");
    printf("- If there is at least one 7: you get your bet back.\n");
    printf("- If all numbers are the same: your bet is doubled.\n");
    printf("- If at least one-third of the numbers are the same: you get your bet back.\n");
}

void printSequence(int sequence[], int length) {
    printf("Sequence: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

void printResult(int win, int coins) {
    if (win) {
        printf("Congratulations! You won %d coins\n", win);
    } else {
        printf("Sorry! You lost your bet!\n");
    }

    if (coins == 0) {
        printf("You've run out of coins!\n");
    }
}

int generateSequence(int sequence[], int length) {
    for (int i = 0; i < length; i++) {
        sequence[i] = rand() % 10;
    }
}

int countFrequency(int sequence[], int length, int frequency[]) {
    for (int i = 0; i < length; i++) {
        frequency[sequence[i]]++;
    }
}

int main() {
    srand(time(NULL));
    int coins = 100;

    printRules();

    while (coins > 0) {
        int bet, win = 0;
        printf("You have %d coins\n", coins);
        printf("Enter your bet (0 to exit): ");
        scanf("%d", &bet);

        if (bet == 0)
            break;
        if (bet > coins) {
            printf("You cannot bet more than you have!\n");
            continue;
        }

        int length;
        printf("Enter the length of the sequence: ");
        scanf("%d", &length);

        if (length > MAX_SEQUENCE_LENGTH || length <= 0) {
            printf("Invalid sequence length. It should be between 1 and %d.\n", MAX_SEQUENCE_LENGTH);
            continue;
        }

        int sequence[MAX_SEQUENCE_LENGTH];
        int frequency[10] = {0};

        generateSequence(sequence, length);

        printSequence(sequence, length);

        for (int i = 0; i < length; i++) {
            if (sequence[i] == 7)
                win = bet;
        }

        countFrequency(sequence, length, frequency);

        for (int i = 0; i < 10; i++) {
            if (frequency[i] == length) {
                win = (i == 7) ? bet * 3 : bet * 2;
                printf("All numbers are the same! Win: %d coins\n", win);
                break;
            }
        }

        for (int i = 0; i < 10; i++) {
            if (frequency[i] >= (length + 2) / 3) {
                if (win == 0) {
                    win = bet;
                    printf("At least one-third of the numbers are the same! Win: %d coins\n", win);
                }
                break;
            }
        }

        coins = coins - bet + win;

        printResult(win, coins);
    }

    printf("Game over!\n");
    printf("You have %d coins left\n", coins);

    return 0;
}
