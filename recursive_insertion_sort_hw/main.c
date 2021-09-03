#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], size_t n, size_t i);
int random_int(int min, int max);

int main(void)
{
    size_t length = 10;
    int s;
    int arr[length];

    for (size_t j = 0; j < length; ++j)
    {
        arr[j] = random_int(1, 10); // populate array
    }

    insertion_sort(arr, 10, 0);

    for (size_t i = 0; i < 10; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}

int random_int(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

void insertion_sort(int arr[], size_t n, size_t i)
{
    int el, j;

    if (i == n - 1)
    {
        return;
    }
    else
    {
        insertion_sort(arr, n, i + 1);
        el = arr[i];

        // All elements to the right of index i are assumed to be sorted.
        // Now we just have to figure out where el fits in the sorted array
        for (j = i + 1; j < n; j++)
        {
            if (el > arr[j])
            {
                // el is bigger, swap so el moves to the right in the array.
                arr[j - 1] = arr[j];
                arr[j] = el;
            }
        }
    }
}
