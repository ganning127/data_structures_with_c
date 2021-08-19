#include <stdio.h>

void grade_average(void);

int main_8_19(void)
{
    int integer1, integer2;

    // puts("Enter an integer: ");
    integer1 = 42;
    // puts("Enter an integer: ");
    integer2 = 54; // scanf("%d", &integer2);

    printf("you entered: %d\n", integer2);
    printf("sum: %d\n", integer1 + integer2);

    char c = 'k';
    // puts("Enter a character");
    // scanf("%c", &c);

    printf("you entered char: %c\n", c);

    return 0;
}

void grade_average(void)
{
    int total = 0;
    int count = 0;
    int grade = 0;

    printf("Enter a grade: ");
    scanf("%d", &grade);

    while (grade != -1)
    {
        printf("Enter a grade: ");
        scanf("%d", &grade);
        total += grade;
        count++;
    }

    printf("Average: %f\n", (double)total / count);
}