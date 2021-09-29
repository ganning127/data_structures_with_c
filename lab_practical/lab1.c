#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void p1(unsigned int n);
void p2(char *strings[], size_t n);
bool p3(unsigned int n);
double p4(char *string);
int p5_helper(int n);
int p5_helper_1(int n);
int p5(int (*p5_helper)(int), unsigned int n);
void showArray(char *arr[], size_t size);

int main(void)
{
    p1(3); // you can change this to test for different cases
    puts("");

    char *names[] = {"Bob", "Apple", "Xu", "Dave", "Dave"}; // you can change this to test for different cases
    size_t n = sizeof(names) / sizeof(names[0]);
    p2(names, n);
    showArray(names, n);
    puts("");

    bool p3_res = p3(6); // you can change this to test for different cases
    printf("perfect number: %s\n", p3_res == 1 ? "true" : "false");
    puts("");

    double p4_res = p4("3.14"); // you can change this to test for different cases
    printf("double %f\n", p4_res);
    puts("");

    int p5_res = p5(&p5_helper_1, 4); // you can change this to test for different cases
    printf("sum: %d\n", p5_res);
    return 0;
}

void p1_top(unsigned int n)
{
    static int star_num = 1;
    if (n < 2)
        return;
    if (star_num <= n)
    {
        printf("*");
        ++star_num;
        p1_top(n);
    }
    else
    {
        printf("\n");
        star_num = 1;
        p1_top(n - 1);
    }
}

void star(unsigned int n)
{
    if (n == 0)
        return;
    printf("*");
    star(n - 1);
}

void p1_bottom(unsigned int n)
{
    static int star_num = 1;
    if (n == 0)
        return;
    star(star_num);
    printf("\n");
    ++star_num;
    p1_bottom(n - 1);
}
void p1(unsigned int n)
{
    // DONE
    p1_top(n);
    p1_bottom(n);
}

void p2(char *strings[], size_t n)
{
    // uses selection sort to sort the array in place
    char *temp;
    size_t min_index;
    for (size_t i = 0; i < n; ++i)
    {
        min_index = i;

        for (size_t j = i + 1; j < n; ++j)
        {
            if (strcmp(strings[j], strings[min_index]) < 0)
            {
                min_index = j;
            }
        }

        temp = strings[min_index];
        strings[min_index] = strings[i];
        strings[i] = temp;
    }
}

bool p3(unsigned int n)
{
    // DONE
    if (n == 1 || n == 0)
        return false;
    unsigned int sum = 0;
    for (int i = 1; i <= n / 2; ++i)
    {
        if (n % i == 0)
            sum += i;
    }

    return n == sum ? true : false;
}

double p4(char *string)
{
    double result = 0.0;
    double factor = 0.0;

    while (*string != '\0')
    {
        if (*string >= '0' && *string <= '9')
        {
            result = 10.0 * result + (double)(*string - '0');
            factor *= 10.0; // determines where to place the decimal point
        }
        else if (*string == '.')
            factor = 1.0;
        string++;
    }

    return result / (factor == 0.0 ? 1.0 : factor);
}

int p5_helper(int n)
{
    return n * n;
}

int p5_helper_1(int n)
{
    return 100 - n;
}

int p5(int (*p5_helper)(int), unsigned int n)
{
    // DONE
    int sum = 0;
    for (unsigned int i = 0; i <= n; ++i)
    {
        sum += (*p5_helper)(i);
    }
    return sum;
}

void showArray(char *arr[], size_t size)
{
    // prints the array to screen
    for (size_t i = 0; i < size; ++i)
    {
        printf("%s ", arr[i]);
    }

    printf("\n");
}