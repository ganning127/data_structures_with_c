#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], size_t index1, size_t index2);
void putMedianInMiddle(int arr[], size_t length);
void quickSort(int arr[], size_t length);
void showArray(int arr[], size_t length);
int main(void)
{
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    size_t length = sizeof(arr) / sizeof(arr[0]);
    showArray(arr, length);

    quickSort(arr, length);

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

void quickSort(int arr[], size_t length)
{
    if (length <= 1)
        return;
}

void swap(int arr[], size_t index1, size_t index2)
{
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

void putMedianInMiddle(int arr[], size_t length)
{
    // put the most likely median element in the midle of the array
    /*
        if first > middle:
            swap
        if middle > last:
            swap
        if first > middle:
            swap
    */

    int middle = length / 2;
    int first = arr[0];
    int last = arr[length - 1];
    if (first > middle)
    {
        swap(arr, 0, middle);
    }
    if (middle > last)
    {
        swap(arr, middle, length - 1);
    }
    if (first > middle)
    {
        swap(arr, 0, middle);
    }
}

/*
QuickSort()
    1. Take three random elements, and take the median of those three elements as the pivot.
    2. Put that median in the center of the array.
    3. Partition the array into two parts, one with elements less than the pivot, one with elements greater than the pivot
    4. Call QuickSort() on each half
    Choose another pivot in the middle of the two parts again
    Algorithm should be in-place
*/