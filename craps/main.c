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
        records[i] = 0;
    }

    // seed random
    srand(42);

    /*
        LOSS = 0
        WIN = 1
    */
    int result;

    // play the game 1000 times
    for (size_t j = 0; j < 1000; ++j)
    {
        result = play_game();
        total_rolls += rolls;
        ++records[result];
        // printf("result: %d\n", result);
        // printf("\n");
    }

    double chance_of_winning;
    chance_of_winning = (double)records[1] / (records[0] + records[1]);

    printf("final results\n------------\n");
    printf("losses: %d\n", records[0]);
    printf("wins: %d\n", records[1]);
    printf("chance of winning: %.2f%%\n", chance_of_winning);
    printf("average rolls before game end: %.2f\n", (double)total_rolls / 1000);
}

int play_game(void)
{
    // function runs the craps game

    game_state = CONTINUE;

    unsigned int point = roll_die(6) + roll_die(6);
    rolls = 1;
    game_state = check_first_roll(point);

    while (game_state == CONTINUE)
    {
        ++rolls;
        unsigned int rolled_point = roll_die(6) + roll_die(6);
        game_state = check_roll(point, rolled_point);
    }

    return (int)game_state;
}

enum Status check_roll(unsigned int point, unsigned int rolled_point)
{
    // checks whether or not the user wins or not on every roll execpt for the first one
    enum Status game_state;

    if (rolled_point == 7)
    {
        game_state = LOST;
    }
    else if (rolled_point == point) // switch can't be used to test against a variable
    {
        game_state = WON;
    }
    else
    {
        game_state = CONTINUE;
    }

    return game_state;
}

enum Status check_first_roll(unsigned int point)
{
    // checks whether or not the user won on the first roll
    enum Status game_state;

    switch (point)
    {
    case 7:
    case 11:
        game_state = WON;
        break;
    case 2:
    case 3:
    case 12:
        game_state = LOST;
        break;
    default:
        game_state = CONTINUE;
    }

    return game_state;
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
