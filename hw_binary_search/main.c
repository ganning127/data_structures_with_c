#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
void fillArrayWithEven(int arr[], size_t size);
void showArray(int arr[], size_t end);
int binarySearch(int arr[], size_t end, int key);
int main(void)
{
    size_t length = 1000;
    int arr[length];

    fillArrayWithEven(arr, length);
    // showArray(arr, length);

    int test1 = binarySearch(arr, length, -65);
    printf("test1 (-65): %d\n", test1); // -1

    int test2 = binarySearch(arr, length, 11);
    printf("test2 (11): %d\n", test2); // -1

    int test3 = binarySearch(arr, length, 2005);
    printf("test3 (2005): %d\n", test3); // -1

    int test4 = binarySearch(arr, length, -2);
    printf("test4 (-2): %d\n", test4); // -1

    int test5 = binarySearch(arr, length, 100);
    printf("test5 (100): %d\n", test5); // 49

    int test6 = binarySearch(arr, length, 2002);
    printf("test6 (2002): %d\n", test6); // -1

    return 0;
}

void showArray(int arr[], size_t size)
{
    // prints the array to screen
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void fillArrayWithEven(int arr[], size_t size)
{
    // fills array with even nums from 2-2000
    for (size_t i = 0, counter = 2; i < size; i++, counter += 2)
    {
        arr[i] = counter;
    }
}

int binarySearch(int arr[], size_t end, int key)
{
    if (end == 0)
        return -1;

    size_t middle = end / 2; // middle of search range
    int found;               // index of the key element

    if (arr[middle] == key)
    {
        found = middle;
    }
    else if (arr[middle] < key)
    {
        found = binarySearch(arr + middle + 1, end - middle - 1, key); // search for the "right" half of the array
        if (found != -1)
        {
            found += middle + 1;
        }
    }
    else
    {
        found = binarySearch(arr, middle, key); // search the "left" half of the array
    }

    return found; // return index of found element
}