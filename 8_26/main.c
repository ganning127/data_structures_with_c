#include <stdio.h>

void statis(void);
unsigned int factorial(unsigned int x);
unsigned int fib(int num);
unsigned int it_fib(int num);

int main(void)
{

    // a scope

    // for (int i = 0; i < 10; ++i)
    // {
    //     statis();
    // }
    unsigned int res = it_fib(21);
    printf("%d\n", res);
    return 0;
}

unsigned int it_fib(int num)
{
    unsigned int a = 1, b = 0;

    for (int i = 0; i < num; ++i)
    {
        b = a + b;
        a = b - a;
    }

    return b;
}

unsigned int fib(int num)
{
    // static unsigned int count;
    // ++count;
    // printf("count: %d\n", count);
    if (num < 2)
        return num;
    return fib(num - 1) + fib(num - 2);
}

unsigned int factorial(unsigned int x)
{
    if (x == 1 || x == 0)
        return 1;

    return factorial(x - 1) * x;
}

void statis(void)
{
    static int x = 0; // the value is STORED between func calls. this line is called only once, after that, it is ignored

    ++x; // goes from 1-10

    printf("x: %d\n", x);
}