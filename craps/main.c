#include <stdio.h>
#include <time.h>
#include <stdlib.h>

enum Status
{
    CONTINUE,
    WON,
    LOST
} game_state;
int rolls;

unsigned int roll_die(unsigned int s);
enum Status check_first_roll(unsigned int point);
int check_game_state(enum Status game_state, unsigned int point);
enum Status check_roll(unsigned int point, unsigned int rolled_point);
int play_game(void);

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
        printf("result: %d\n", result);
        printf("\n");
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

    int result;

    game_state = CONTINUE;

    unsigned int point = roll_die(6) + roll_die(6);
    rolls = 1;
    game_state = check_first_roll(point);
    result = check_game_state(game_state, point);

    // printf("Point: %d\n", point);

    while (game_state == CONTINUE)
    {
        ++rolls;
        unsigned int rolled_point = roll_die(6) + roll_die(6);
        // printf("rolled_score: %d\n", rolled_point);
        game_state = check_roll(point, rolled_point);
        result = check_game_state(game_state, rolled_point);
    }

    return result;
}

enum Status check_roll(unsigned int point, unsigned int rolled_point)
{
    enum Status game_state;

    if (rolled_point == 7)
    {
        game_state = LOST;
    }
    else if (rolled_point == point)
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

int check_game_state(enum Status game_state, unsigned int point)
{
    if (game_state == WON)
    {
        // printf("You have rolled a %d, and won!\n", point);
        return 1;
    }
    else if (game_state == LOST)
    {
        // printf("You have rolled a %d, and lost :(\n", point);
        return 0;
    }
    return -1; // represents `CONTINUE`
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
