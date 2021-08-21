#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], int n)
{

    int curr, less_index;

    for (int i = 1; i < n; ++i)
    {
        curr = arr[i];
        less_index = i - 1;

        while (curr < arr[less_index] && less_index >= 0)
        {
            arr[less_index + 1] = arr[less_index];
            less_index -= 1;
        }
        arr[less_index + 1] = curr;
    }
}