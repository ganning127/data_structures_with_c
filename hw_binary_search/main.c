#include <stdio.h>
#include <stdlib.h>
int binarySearch(int arr[], size_t end, int target);
void fillArrayWithEven(int arr[], size_t size);
void showArray(int arr[], size_t end);

int main(void)
{
    size_t length = 10;
    int arr[length];

    fillArrayWithEven(arr, length);
    showArray(arr, length);

    int index = binarySearch(arr, length, 6);
    printf("Index: %d\n", index);
    return 0;
}

void showArray(int arr[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void fillArrayWithEven(int arr[], size_t size)
{
    for (size_t i = 0, counter = 2; i < size; i++, counter += 2)
    {
        arr[i] = counter;
    }
}

int binarySearch(int arr[], size_t end, int target)
{
    size_t middle = end / 2;

    printf("middle: %zu\n", middle);
    if (arr[middle] == target)
    {
        return middle;
    }
    else
    {
        if (target > arr[middle])
            return binarySearch(arr, arr + end / 2, target);

        else
            return binarySearch(arr, end / 2, target);
    }
}

/*
BINARY SEARCH:
    *don't need min and max index*
    pass in array, size, target
    Check middle
    if not value:
        call again on either (array and size/2)or (array+size/2 and size/2)
    else:
        return index
*/