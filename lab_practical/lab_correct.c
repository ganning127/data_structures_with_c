#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p1(unsigned int n);
void p2(char *strings[], size_t n);
bool p3(unsigned int n);
double p4(char *string);
int p5(unsigned int n, int (*p5_helper)(int));
int main(void)
{
    p1(3);

    char *names[] = {"Xu", "Dave", "Bob"};
    size_t n = sizeof(names) / sizeof(names[0]);
    p2(names, n);
    for (size_t i = 0; i < n; ++i)
        printf("%s ", names[i]);
    puts("");

    printf("perfect: %d\n", p3(6));
    printf("%.10f\n", p4("1010.12"));
    return 0;
}

void p1(unsigned int n)
{
    if (n == 1)
        printf("*\n");
    else
    {
        for (unsigned int i = 1; i <= n; ++i)
            printf("*");
        printf("\n");
        p1(n - 1);
        for (unsigned int i = 1; i <= n; ++i)
            printf("*");
        printf("\n");
    }
}

void p2(char *strings[], size_t n)
{
    char *temp;
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = 0; j < n - i - 1; ++j)
        {
            if (strcmp(strings[j], strings[j + 1]) > 0)
            {
                temp = strings[j];
                strings[j] = strings[j + 1];
                strings[j + 1] = temp;
            }
        }
    }
}

bool p3(unsigned int n)
{
    unsigned int sum = 0;

    for (unsigned int i = 1; i <= n / 2; ++i)
    {
        if (n % i == 0)
            sum += i;
        if (sum > n)
            return false;
    }

    return n == sum ? true : false;
}

double p4(char *string)
{

    size_t i;
    bool negative;
    if (string[0] == '-')
    {
        i = 1; // want to skip over in for loop
        negative = true;
    }
    double val = 0;
    for (i = 0; string[i] != '.' && string[i] != 0; ++i)
        val = val * 10 + string[i] - '0';
    if (string[i] == 0)
        return val * (negative ? -1 : 1);
    i += 1;
    for (double decimal = 10; string[i] != '0'; ++i, decimal *= 10)
        val += (string[i] - '0') / decimal;
    return val * (negative ? -1 : 1);
    ;
}

int p5(unsigned int n, int (*p5_helper)(int))
{
    int sum = 0;
    for (unsigned int k = 0; k <= n; ++k)
    {
        sum += (*p5_helper)(n);
    }

    return sum;
}