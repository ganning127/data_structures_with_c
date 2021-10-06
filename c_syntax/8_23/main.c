#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], size_t n); // change int n to size n
void selection_sort(int arr[], size_t n);
void show(int arr[], size_t n);

int main(void)
{
    // int x = 0;
    // do
    // {
    //     if (x == 5)
    //         continue;

    //     printf("%d\n", x);
    // } while (++x < 10);

    printf("%d\n", EOF);
    char grade;
    unsigned int grades[5] = {0};

    while ((grade = getchar()) != EOF) // typing in a newline character as well, so it will be 'a\n', and runs twice
    {

        if (grade >= 'A' && grade <= 'E')
        {
            grades[grade - 'A'] += 1; // grade is a char, and an integer, just subtracting A gives you 0 index for A, 1 for B, etc..
        }
        // switch (grade)
        // {
        // case 'A':
        //     ++grades[0];
        //     break; // if you don't have break, anything below the case that matches will be run.
        // case 'B':  // so if it was `B` with no break, typing in a B will increment everything except for A
        //     ++grades[1];
        //     break;
        // case 'C':
        //     ++grades[2];
        //     break;
        // case 'D':
        //     ++grades[3];
        //     break;
        // case 'E':
        //     ++grades[4];
        //     break;
        // default:
        //     puts("not a grade");
        // }
    }

    printf("\n");
    for (size_t i = 0; i < 5; i++)
    {
        printf("%i\n", grades[i]);
    }
    return 0;
}
