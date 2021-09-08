#include <stdbool.h>
#include <stdio.h>
#include <time.h> // handled by preprocessor

void bubble_sort(int a[], int n) // `void` means that there is no return
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int temp, j; // both are int
    bool sorted = false;

    for (j = 0, sorted = false; j < n - 1 && !sorted; j++) // how many times to loop through entire thing
    {
        sorted = true; // assume is sorted
        for (int i = 0; i < n - 1 - j; i++)
        {
            if (a[i] > a[i + 1])
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                sorted = false; // arr not sorted
            }
        }
    }
    // printf("%d\n", j);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
}
