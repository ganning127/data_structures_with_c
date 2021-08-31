#include <stdio.h>
#include <time.h>
#include <stdlib.h>

enum Status
{
    LOST,
    WON,
    CONTINUE
} game_state;
int rolls;

unsigned int roll_die(unsigned int s);
enum Status check_first_roll(unsigned int point);
enum Status check_roll(unsigned int point, unsigned int rolled_point);
int play_game(void);

// add the number of rolls all together and divide by 1000
int main(void)
{
    // populate array with zeros
    int records[2];
    int total_rolls = 0;
    for (size_t i = 0; i < 2; ++i)
    {
        records[i] = 0; // records holds the number of wins (index 1), and number of losses (index 0)
    }

    // seed random
    srand(42);

    int result; // win = 1, loss = 0

    // play the game 1000 times
    for (size_t j = 0; j < 1000; ++j)
    {
        // play the game 1000 times
        result = play_game();
        total_rolls += rolls;
        ++records[result];
    }

    double chance_of_winning;
    chance_of_winning = (double)records[1] / (records[0] + records[1]); // number of wins divided by total

    // chances of winning to 2 decimal places, length of game to 2 decimal places
    printf("final results\n------------\n");
    printf("losses: %d\n", records[0]);
    printf("wins: %d\n", records[1]);
    printf("chance of winning: %.2lf%%\n", chance_of_winning);
    printf("average rolls before game end: %.2lf\n", (double)total_rolls / 1000);
}

int play_game(void)
{
    // function runs the craps game
    game_state = CONTINUE;

    unsigned int point = roll_die(6) + roll_die(6); // initial point
    game_state = check_first_roll(point);           // either: CONTINUE, LOST, WON

    for (rolls = 1; game_state == CONTINUE; ++rolls)
    {
        // game loops until the user WON / LOSt
        unsigned int rolled_point = roll_die(6) + roll_die(6);
        game_state = check_roll(point, rolled_point);
    }

    return (int)game_state; // won = 1, loss = 0
}

enum Status check_roll(unsigned int point, unsigned int rolled_point)
{
    // checks whether or not the user wins or not on every roll execpt for the first one
    if (rolled_point == 7)
    {
        return LOST;
    }
    else if (rolled_point == point) // switch can't be used to test against a variable
    {
        return WON;
    }
    else
    {
        return CONTINUE;
    }
}

enum Status check_first_roll(unsigned int point)
{
    // checks whether or not the user won on the first roll

    switch (point)
    {
    case 7:
    case 11:
        return WON;
    case 2:
    case 3:
    case 12:
        return LOST;
    default:
        return CONTINUE;
    }
}

unsigned int roll_die(unsigned int s)
{
    // generates a random number between [0, s]
    unsigned int remainder = RAND_MAX % s;
    unsigned int roll;

    do
    {
        roll = rand();
    } while (roll >= RAND_MAX - remainder);
    return roll % s + 1;
}