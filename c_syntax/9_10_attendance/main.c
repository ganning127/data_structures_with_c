#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // argv is an array of strings
    int result = atoi(argv[1]); // 0th element is the `./programName`

    for (size_t i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "+") == 0)
        {
            // addition
            result += atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-") == 0)
        {
            // subtraction
            result -= atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "*") == 0)
        {
            // multiplication
            result *= atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "/") == 0)
        {
            // division
            result /= atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "^") == 0)
        {
            // powers
            result = pow(result, atoi(argv[i + 1]));
        }
    }
    printf("%d\n", result);

    return 0;
}