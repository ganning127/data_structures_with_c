#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], size_t i);
int random_int(int min, int max);
void insert(int arr[], size_t i);

int main(void)
{
    size_t length = 10;
    int s;
    int arr[length];

    for (size_t j = 0; j < length; ++j)
    {
        arr[j] = random_int(1, 10); // populate array
        printf("%d ", arr[j]);
    }

    printf("\n");

    insertion_sort(arr, length);

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

void insert(int arr[], size_t i)
{
    if (i == 0)
        return;

    if (arr[i] < arr[i - 1])
    {
        int temp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = temp;
    }

    insert(arr, i - 1);
}

void insertion_sort(int arr[], size_t i)
{
    if (i == 0)
        return;

    insertion_sort(arr, i - 1);

    insert(arr, i);
}

/*
    function insert()
        base case: 
            at index 0, just use return; (no value)
        otherwise: 
            compare to prev element, and swap if necessary.
            recursive function call on array and index-1

    function insertion_sort()
        **start at end of the array (pass in size)
        base_case:
            at the beginning, juse use return; (no value)
        otherwise:
            recursive function call on array and index-1
            insert current index into sorted array using insert().
            decrement static index
*/