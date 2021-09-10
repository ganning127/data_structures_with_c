#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
void fillArrayWithEven(int arr[], size_t size);
void showArray(int arr[], size_t end);
int binarySearchRecursive(int arr[], size_t end, int target);
int main(void)
{
    int length = 1000;
    int arr[length];

    fillArrayWithEven(arr, length);
    // showArray(arr, length);

    int test1 = binarySearchRecursive(arr, length, -65);
    printf("test1 (-65): %d\n", test1); // -1

    int test2 = binarySearchRecursive(arr, length, 11);
    printf("test2 (11): %d\n", test2); // -1

    int test3 = binarySearchRecursive(arr, length, 2005);
    printf("test3 (2005): %d\n", test3); // -1

    int test4 = binarySearchRecursive(arr, length, -2);
    printf("test4 (-2): %d\n", test4); // -1

    int test5 = binarySearchRecursive(arr, length, 100);
    printf("test5 (100): %d\n", test5); // 49

    int test6 = binarySearchRecursive(arr, length, 2002);
    printf("test6 (2002): %d\n", test6); // -1
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

int binarySearchRecursive(int arr[], size_t end, int target)
{
    if (end == 0)
    {
        return -1;
    }

    int m = end / 2; // middle of search scope
    int found;

    if (arr[m] == target)
    {
        found = m;
    }
    else if (arr[m] < target)
    {
        // Upper half. We'll search in upper half of the current array with new length of the upper half
        found = binarySearchRecursive(arr + m + 1, end - m - 1, target);
        if (found != -1)
        {
            // Need to offset the key
            found += m + 1;
        }
    }
    else
    {
        // Lower half, there is no need to offset the array
        // New array length is equal to the current middle point
        found = binarySearchRecursive(arr, m, target);
    }

    return found;
}