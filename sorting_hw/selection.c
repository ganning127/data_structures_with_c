#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);

int *find_max(int arr[], int n, int start_index)
{
    int max = arr[start_index];    // set `max` equal to the starting index of unsorted array
    int *pmax = &arr[start_index]; // set pointer to max equal to the address of the starting index of the unsorted array
    for (int i = start_index; i < n; ++i)
    {
        if (arr[i] > max) // checks if current element is greater than the current max
        {
            max = arr[i];   // reassign new max value
            pmax = &arr[i]; // reassign new max pointer
        }
    }

    return pmax; // return pointer to the max element in the array
}

void selection_sort(int arr[], int n)
{
    // `selection_sort()` sorts an array in descending (largest to smallest)
    int sorted_start = 0; // index of the sorted array

    for (sorted_start = 0; sorted_start < n; ++sorted_start)
    {
        int *max = find_max(arr, n, sorted_start); // max stores a pointer to the max value in arr
        swap(&arr[sorted_start], max);             // swap the max value with the starting value of the unsorted array
    }
}

void swap(int *x, int *y)
{
    // function swaps the values of x and y
    int temp = *x;
    *x = *y;
    *y = temp;
}