#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_SUITS 4
#define NUM_FACES 13

typedef struct card
{
    char *face;
    char *suit;
    unsigned int number;
} Card;

void fillDeck(Card *deck, char *faces[], char *suits[]);
void shuffle(Card *deck);
void deal(Card *deck);
int random_int(int min, int max);

int main(void)
{
    /*
        In the main function, declare the deck, initialize the arrays of strings for the names of faces in suits, Ace high and in the order of Diamonds, Clubs, Hearts, and Spades
    */

    char *suits[] = {
        "Diamonds",
        "Clubs",
        "Hearts",
        "Spades",
    };

    char *faces[] = {
        "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

    srand(42); // seed random number generator

    Card card_arr[NUM_SUITS * NUM_FACES];

    fillDeck(card_arr, faces, suits);
    shuffle(card_arr);
    deal(card_arr);
    return 0;
}

void fillDeck(Card *deck, char *faces[], char *suits[])
{
    for (size_t i = 0; i < NUM_FACES * NUM_SUITS; ++i)
    {
        deck[i].face = faces[i % NUM_FACES];
        deck[i].suit = suits[i / NUM_FACES];
        deck[i].number = i % NUM_FACES + 2;
    }
}
void shuffle(Card *deck)
{
    // shuffle deck with Fisher-yates method
    for (size_t i = 0; i < NUM_SUITS * NUM_FACES; ++i)
    {
        int swap_num = rand() % (NUM_SUITS * NUM_FACES - i);
        Card temp = deck[NUM_FACES * NUM_SUITS - i - 1];
        deck[NUM_FACES * NUM_SUITS - i - 1] = deck[swap_num];
        deck[swap_num] = temp;
    }
}
void deal(Card *deck)
{
    for (size_t i = 0; i < NUM_FACES * NUM_SUITS; ++i)
        printf("%s of %s\n", deck[i].face, deck[i].suit);
}

int random_int(int min, int max)
{
    // returns num from [min, max]
    return min + rand() % (max + 1 - min);
}