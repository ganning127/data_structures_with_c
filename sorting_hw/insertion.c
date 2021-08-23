#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], size_t n)
{

    int curr;          // `curr` stores the current element in the array
    size_t less_index; // `less_index` stores indexes less than the current one

    for (size_t i = 1; i < n; ++i)
    {
        curr = arr[i];      // current element index
        less_index = i - 1; // previous element index

        while (curr < arr[less_index] && less_index >= 0)
        {
            arr[less_index + 1] = arr[less_index]; // move elements that are greater than current element up one position
            less_index -= 1;                       // check previous elements
        }
        arr[less_index + 1] = curr; // moves the current element to where it is no longer less than the previous element
    }
}