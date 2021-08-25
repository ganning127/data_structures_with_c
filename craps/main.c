#include <stdio.h>
#include <time.h>
#include <stdlib.h>

enum Status
{
    CONTINUE,
    WON,
    LOST
} game_state;

unsigned int roll_die(unsigned int s);
enum Status check_first_roll(unsigned int point);
void check_game_state(enum Status game_state, unsigned int point);
enum Status check_roll(unsigned int point, unsigned int rolled_point);

int main(void)
{
    game_state = CONTINUE;

    /* Obtain current time. */
    time_t current_time = time(NULL);
    srand(current_time); // seeds random

    unsigned int point = roll_die(6) + roll_die(6);
    game_state = check_first_roll(point);
    check_game_state(game_state, point);

    printf("Point: %d\n", point);

    while (game_state == CONTINUE)
    {
        unsigned int rolled_point = roll_die(6) + roll_die(6);
        // printf("rolled_score: %d\n", rolled_point);
        game_state = check_roll(point, rolled_point);
        check_game_state(game_state, rolled_point);
    }
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
    if (point == 7 || point == 11)
    {
        game_state = WON;
    }
    else if (point == 2 || point == 3 || point == 12)
    {
        game_state = LOST;
    }
    else
    {
        game_state = CONTINUE;
    }

    return game_state;
}

void check_game_state(enum Status game_state, unsigned int point)
{
    if (game_state == WON)
    {
        printf("You have rolled a %d, and won!\n", point);
    }
    else if (game_state == LOST)
    {
        printf("You have rolled a %d, and lost :(\n", point);
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
