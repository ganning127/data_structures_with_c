#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

unsigned int problem1(unsigned int n);
unsigned int problem2(unsigned int n);
bool problem3(char *string);
bool p3_helper(char *string, size_t length);
unsigned int p4(char *string);
char *problem5(char *string, int shift);

int main(void)
{
    unsigned int p1_res = problem1(10);
    printf("zeros: %d\n", p1_res);

    bool p3_res = problem3("racecar");
    printf("palindrome: %d\n", p3_res);

    unsigned int p4_res = p4("Z6");
    printf("lowest base: %u\n", p4_res);

    problem5("xyz", 1);
    return 0;
}

unsigned int problem1(unsigned int n)
{
    srand(42);
    unsigned int ones = 0; // don't use size_t, because we are not dealing with memory. ones can get infinitly large depending on n
    for (unsigned int i = 0; i < n; ++i)
    {
        ones += rand() % 2;
    }
    return n - ones;
}

unsigned int problem2(unsigned int n)
{
    srand(42);
    unsigned int rolls;
    bool roll = true;
    int die; // die will only be from 0-6
    unsigned int i;

    // roll die
    for (rolls = 1; roll == true; ++rolls)
    {
        roll = false;
        die = rand() % 6;
        for (i = 1; i < n; ++i)
        {
            if (rand() % 6 != die)
            {
                roll = true;
                break; // non equal
            }
        }
    }
    return rolls;
}

bool problem3(char *string)
{
    size_t length = strlen(string);

    return p3_helper(string, length);
}

bool p3_helper(char *string, size_t length)
{
    if (length < 2)
        return true;
    if (string[0] != string[length - 1])
        return false;
    return p3_helper(string + 1, length - 2);
}

unsigned int p4(char *string)
{
    unsigned int base = 2, current;
    for (size_t i = 0; i < string[i] != 0; ++i)
    {
        if (string[i] >= '0' && string[i] <= '9')
        {
            current = string[i] - '0' + 1;
        }
        else if (string[i] >= 'A' && string[i] <= 'Z')
        {
            current = string[i] - 'A' + 11;
        }

        base = base > current ? base : current; // assign larger of `base` and `current` to base
    }

    return base;
}

char *problem5(char *string, int shift)
{
    char *ct = malloc(sizeof(char) * strlen(string));
    ct[strlen(string)] = 0;

    for (size_t i = 0; string[i] != 0; ++i)
    {
        ct[i] = (string[i] - 'a' + shift) % 26 + 'A';
        // -'a' to shift alphabet to zero
        // %26 makes sure that the alphabet is within bounds of the alphabet
        // + 'A' makes the character positive again
    }

    return ct;
}