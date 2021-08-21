#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int *find_min(int arr[], int n, int start_index)
{
    int min = arr[start_index];
    int *pmin = &arr[start_index];
    for (int i = start_index; i < n; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            pmin = &arr[i];
        }
    }

    return pmin;
}

void selection_sort(int arr[], int n)
{

    // sort the array
    // 10, 9, 2, 8, 12, 45

    int sorted_start = 0;

    for (sorted_start = 0; sorted_start < n; ++sorted_start)
    {
        int *min = find_min(arr, n, sorted_start); // min stores a pointer to the min value
        swap(&arr[sorted_start], min);
    }

    // print the array out
    for (int z = 0; z < n; ++z)
    {
        printf("%d\n", arr[z]);
    }
}

// CHANGE UP THIS CODE BEFORE TURNING IN BC IT IS COPIED