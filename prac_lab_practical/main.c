#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int coin_flip(int n);
int dice_roll(int n);
bool palindrome(char *str, int start, int end);
char *caesar_shift(char *str, int n);
int lowest_base(char *str);
bool isPalindrome(char *str);

void showArray(int arr[], size_t size);

int main(void)
{
    srand(42);
    int q1_result = coin_flip(10);
    int q1_result_1 = coin_flip(20);
    printf("[test 1] (10 flips) 0s: %d\n", q1_result);
    printf("[test 2] (20 flips) 0s: %d\n", q1_result_1);

    puts("");
    int q2_result = dice_roll(2);
    int q2_result_1 = dice_roll(5);
    printf("[test 1] (2 dice) Rolls required: %d\n", q2_result);
    printf("[test 2] (5 dice) Rolls required: %d\n", q2_result_1);

    puts("");
    bool q3_result = isPalindrome("ganninnag");
    bool q3_result_1 = isPalindrome("ganninnfag");
    printf("[test 1] (`ganninnag`) Is palindrome: %s\n", q3_result == 1 ? "true" : "false");
    printf("[test 2] (`ganninnfag`) Is palindrome: %s\n", q3_result_1 == 1 ? "true" : "false");

    puts("");
    int q4_result = lowest_base("1010");
    int q4_result_1 = lowest_base("Z5");
    printf("[test 1] (`1010`) Lowest base: %d\n", q4_result);
    printf("[test 2] (`Z5`) Lowest base: %d\n", q4_result_1);

    puts("");
    char *q5_result = caesar_shift("xyz", 1);
    char *q5_result_1 = caesar_shift("abc", 4);
    printf("[test 1] (`xyz`, 1) Shifted: %s\n", q5_result);
    printf("[test 2] (`abc`, 25) Shifted: %s\n", q5_result_1);
    free(q5_result);
    free(q5_result_1);

    return 0;
}

int lowest_base(char *str)
{
    size_t length = strlen(str);
    int max = str[0];

    for (size_t i = 0; i < length; ++i)
    {
        if (str[i] > max)
            max = str[i];
    }

    if (max >= 58)
        max -= 54;
    else
        max -= 47;

    return max;
}

char *caesar_shift(char *str, int n)
{
    // this function will print the letters out correctly, but will not return the string
    int index = 0;
    char current_char = str[index];
    char *final = malloc(sizeof(str) * strlen(str));

    strcpy(final, str);

    while (current_char != 0)
    {
        char temp = str[index];
        temp += n;

        while (temp >= 123)
            temp -= 26; // gets the letter back in the alphabet range

        temp -= 32;                // lowercase - 32 = uppercase
        final[index] = (char)temp; // this line causes a error idk why
        current_char = str[++index];
    }
    return final;
}

bool isPalindrome(char *str)
{
    size_t length = strlen(str);

    if (length == 0)
        return true;

    return palindrome(str, 0, length - 1);
}

bool palindrome(char *str, int start, int end)
{
    // Write a recursive function that determines if a string is a palindrome and returns True or False.
    if (str[start] != str[end])
        return false;
    else if (end < start + 1)
        return true;

    // printf("called\n");
    return palindrome(str, ++start, --end);
}

int coin_flip(int n)
{
    // Seed the RNG with 42. Write a function that flips a coin (0 or 1) n times and returns the number of 0s rolled.
    int results[2] = {0, 0};
    for (size_t i = 0; i < n; ++i)
    {
        int zero_or_one = rand() % 2;
        ++results[zero_or_one];
    }

    return results[0];
}

int dice_roll(int n)
{
    // Seed the RNG with 42. Write a function that rolls n 6-sided dice and returns the number of rolls required until they all match.
    int dice_results[n];
    int completed = 0; // 0 = false; 1 = true
    int counter = 0;

    while (completed != 1)
    {
        // reroll dice
        for (size_t i = 0; i < n; ++i)
        {
            int num = rand() % 6 + 1;
            dice_results[i] = num;
        }

        counter++;

        // showArray(dice_results, sizeof(dice_results) / sizeof(dice_results[0]));
        for (size_t i = 1; i < n; ++i)
        {
            int sample = dice_results[0]; // first element of array to check if all are equal

            if (dice_results[i] != sample)
            {
                completed = 0;
                break;
            }
            completed = 1;
        }
    }
    return counter;
}

void showArray(int arr[], size_t size)
{
    // prints the array to screen
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}
