#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int *find_max(int arr[], int n, int start_index)
{
    int max = arr[start_index];
    int *pmax = &arr[start_index];
    for (int i = start_index; i < n; ++i)
    {
        if (arr[i] > max) // put the largest element first
        {
            max = arr[i];
            pmax = &arr[i];
        }
    }

    return pmax;
}

void selection_sort(int arr[], int n)
{
    // `selection_sort()` sorts an array in descending (largest to smallest)
    int sorted_start = 0;

    for (sorted_start = 0; sorted_start < n; ++sorted_start)
    {
        int *max = find_max(arr, n, sorted_start); // min stores a pointer to the min value
        swap(&arr[sorted_start], max);
    }
}