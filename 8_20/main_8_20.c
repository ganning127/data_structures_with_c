#include <stdio.h>
#include <limits.h>

int main_8_20(void)
{

    int x = 23;

    // printf("%d\n", x << 1); // multiplies by 2
    // printf("%f\n", 6.28);

    // printf("%d\n", 6.28); // tries to directly interpret float as integer

    size_t s = -1;
    unsigned long i = ULONG_MAX;
    printf("%zu %lu\n", s, i);
    return 0;
}