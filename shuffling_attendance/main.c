#include <stdio.h>
#include <stdlib.h>
#define NUM_SUITS 4
#define NUM_FACES 13

typedef struct card
{
    char *face;
    char *strings;
    unsigned int number;

    struct card *friend; // student.friend is a pointer
} Card;

void fillDeck(Card *deck, char *faces[], char *suits[]);
void shuffle(Card *deck);
void deal(Card *deck);

int main(void)
{
    srand(42); // seed random number generator
    return 0;
}