#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], size_t index1, size_t index2);
void putMedianInMiddle(int arr[], size_t length);
void quickSort(int arr[], size_t length);
void showArray(int arr[], size_t length);
int main(void)
{
    size_t length = 10;
    // put random numbers in array
    int arr[length];
    for (size_t i = 0; i < length; i++)
    {
        arr[i] = rand() % 100 + 13;
    }

    srand(42);
    showArray(arr, length);
    puts("");
    quickSort(arr, length - 1);
    showArray(arr, length);

    return 0;
}

void showArray(int arr[], size_t length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

size_t partitionArray(int arr[], size_t length)
{
    /*
    // j looks for things less  than or equal to the pivot
    // eventually, we just put the pivot where i is
    // i is where you are inseting items when you find an item near the end that is smaler than the pivot
    */

    int pivot = arr[length - 1];
    int i = -1;
    int j = length + 1;
    while (1)
    {
        do
        {
            i++;
        } while (arr[i] < pivot); // not testing for equality against the pivot makes sure that we don't go out of bounds

        do
        {
            j--;
        } while (arr[j] > pivot); // using a do-while loop if the pivots were both at the end

        if (i >= j)
        {
            return j;
        }
        swap(arr, i, j);
    }
}

void quickSort(int arr[], size_t length)
{
    if (length <= 1)
        return;
    putMedianInMiddle(arr, length);
    size_t i = partitionArray(arr, length);
    quickSort(arr, i);
    quickSort(arr + i + 1, length - i - 1);
}

void swap(int arr[], size_t index1, size_t index2)
{
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

void putMedianInMiddle(int arr[], size_t length)
{

    size_t middle = length / 2;
    size_t first = 0;
    size_t last = length - 1;
    // printf("first: %d\n", arr[first]);
    // printf("middle: %d\n", arr[middle]);
    // printf("last: %d\n", arr[last]);

    if (arr[first] > arr[last])
    {
        swap(arr, first, last);
    }
    if (arr[middle] < arr[last])
    {
        swap(arr, middle, last);
    }
    if (arr[first] > arr[last])
    {
        swap(arr, first, last);
    }
}