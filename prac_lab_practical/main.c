#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int q1(int n);
int q2(int n);
bool q3(char *str, int start, int end);
char *q5(char *str, int n);
int q4(char *str);
bool isPalindrome(char *str);

void showArray(int arr[], size_t size);

int main(void)
{
    // int res1 = q1(10);
    // printf("0s: %d\n", res1);

    // int res2 = q2(2);
    // printf("rolls required: %d\n", res2);

    // bool res3 = isPalindrome("ganninnag");
    // printf("%d\n", res3);
    char *res5 = q5("xyz", 1);
    puts(res5);

    // int res4 = q4("38CP");
    return 0;
}

int q4(char *str)
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

char *q5(char *str, int n)
{
    // this function will print the letters out correctly, but will not return the string

    int index = 0;
    char current_char = str[index];

    while (current_char != 0)
    {
        char temp = str[index];
        temp += n;

        while (temp >= 123)
            temp -= 26; // gets the letter back in the alphabet range

        temp -= 32; // lowercase - 32 = uppercase
        // final_result[index] = temp; // this line causes a error idk why
        printf("index %d: %c\n", index, temp);
        current_char = str[++index];
    }
    return str;
}

bool isPalindrome(char *str)
{
    size_t length = strlen(str);

    if (length == 0)
        return true;

    return q3(str, 0, length - 1);
}

bool q3(char *str, int start, int end)
{
    // Write a recursive function that determines if a string is a palindrome and returns True or False.
    if (str[start] != str[end])
        return false;
    else if (end < start + 1)
        return true;

    // printf("called\n");
    return q3(str, ++start, --end);
}

int q1(int n)
{
    // Seed the RNG with 42. Write a function that flips a coin (0 or 1) n times and returns the number of 0s rolled.
    srand(42);
    int results[2] = {0, 0};
    for (size_t i = 0; i < n; ++i)
    {
        int zero_or_one = rand() % 2;
        ++results[zero_or_one];
    }

    return results[0];
}

int q2(int n)
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
        showArray(dice_results, n);

        counter++;
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
