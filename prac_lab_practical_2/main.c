#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

unsigned int p1(unsigned int n);
unsigned int p2(unsigned int num_die);
bool p3(char *string);
unsigned int p4(char *string);
char *p5(char *string, int n);

void showArray(int arr[], size_t size)
{
    // prints the array to screen
    for (size_t i = 0; i < size; ++i)
        printf("%d ", arr[i]);

    printf("\n");
}

int main(void)
{
    unsigned int p1_res = p1(10);
    printf("zeros: %u\n", p1_res);

    unsigned int p2_res = p2(2);
    printf("rolls: %u\n", p2_res);

    bool p3_res = p3("racecfar");
    printf("palindrome: %d\n", p3_res);

    unsigned int p4_res = p4("ZA5");
    printf("lowest base: %u\n", p4_res);

    char *p5_res = p5("xyz", 1);
    printf("shifted: %s\n", p5_res);
    free(p5_res);

    return 0;
}

unsigned int p1(unsigned int n)
{
    // Seed the RNG with 42. Write a function that flips a coin (0 or 1) n times and returns the number of 0s rolled.
    srand(42);
    int arr[2] = {0, 0};

    for (unsigned int i = 0; i < n; ++i)
    {
        unsigned int random_num = rand() % 2;
        ++arr[random_num];
    }

    return arr[0];
}

unsigned int p2(unsigned int num_die)
{
    unsigned int die[num_die];
    unsigned int rolls = 1;
    bool done = true;

    // roll die
    for (size_t i = 0; i < num_die; ++i)
        die[i] = rand() % 6 + 1;

    for (size_t i = 1; i < num_die; ++i)
    {
        if (die[0] != die[i])
        {
            done = false;
            break;
        }
    }

    while (!done)
    {
        done = true;
        for (size_t i = 0; i < num_die; ++i)
            die[i] = rand() % 6 + 1;
        ++rolls;
        for (size_t i = 1; i < num_die; ++i)
        {
            if (die[0] != die[i])
            {
                done = false;
                break;
            }
        }
    }
    return rolls;
}

bool p3_helper(char *string, size_t length)
{
    printf("\n");
    if (string[0] != string[length])
        return false;
    else if (length <= 0)
        return true;
    size_t length_use = length - 2;
    return p3_helper(++string, length_use);
}

bool p3(char *string)
{
    unsigned int length = strlen(string);

    return p3_helper(string, length - 1);
}

unsigned int p4(char *string)
{
    // Write a function that determines the lowest possible base of an input string from 2 to 36, all uppercase, e.g., "1010" should return 2 and "Z5" should return 36.

    unsigned int max = 2;
    unsigned int temp = 0;
    for (size_t i = 0; i < strlen(string) - 1; ++i)
    {
        if (string[i] >= '0' && string[i] <= '9')
            temp = string[i] - '0' + 1;
        else if (string[i] >= 'A' && string[i] <= 'Z')
            temp = string[i] - 'A' + 11; // 11 is the `A` for hex
        max = max > temp ? max : temp;
    }

    return max;
}

char *p5(char *string, int n)
{
    char *final_string = malloc(sizeof(char) * strlen(string));
    final_string[strlen(string) - 1] = 0;
    for (size_t i = 0; i < strlen(string); ++i)
    {
        char temp = (string[i] + n - 'a') % 26 + 'A';
        final_string[i] = temp;
    }

    return final_string;
}