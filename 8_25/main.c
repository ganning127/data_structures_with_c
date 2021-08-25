#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define example 42 // not an variable/integer, but is a piece of text. everywhere that has "example" in the code gets replaced with 42

enum Status
{
    CONTINUE,
    WON,
    LOST
};

// max(int a, int b, int c); works but generates an error in compile

int max(int a, int b, int c);
unsigned int roll_die(unsigned int s);
void record_dice(unsigned int rolls, unsigned int size);

int main(void)
{
    enum Status game_state;
    game_state = WON;

    printf("%d %d %d\n", CONTINUE, WON, LOST);
    /* Obtain current time. */
    time_t current_time = time(NULL);

    srand(current_time); // seeds random
    // record_dice(1000, 20);
    // for (int i = 0; i < 100; ++i)
    // {
    //     printf("%i\n", roll_die(20));
    // }
}

void record_dice(unsigned int rolls, unsigned int size)
{
    unsigned int records[size];

    for (size_t i = 0; i < size; ++i)
    {
        records[i] = 0;
    }

    for (unsigned int roll = 0; roll < rolls; ++roll)
    {
        ++records[roll_die(size) - 1];
    }

    for (size_t i = 0; i < size; ++i)
    {
        printf("%4zu%10d\n", i + 1, records[i]);
    }
}

unsigned int roll_die(unsigned int s)
{
    unsigned int remainder = RAND_MAX % s;
    unsigned int roll;

    do
    {
        roll = rand();
    } while (roll >= RAND_MAX - remainder);
    return roll % s + 1;
}

int max(int a, int b, int c)
{
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
    // return a * (a > b && a > c) + b * (b > a && b > c) + c * (c > a && c > b);
}

/*
    craps:
        - roll 2d6 (two sided die w 6 faces)

        - if 7 or 11, player wins (first row only)
        - else if 2, 3, 12, player loses (first row only)
        - else record sum as "point" (first row only)

        continue rolling until player makes their "point" or rolls a 7 and loses

    
*/

void craps(void)
{
}