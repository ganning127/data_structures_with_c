#include <stdio.h>
#include <stdlib.h>

void selection_sort(int arr[], size_t n)
{
    // this function, `selection_sort()`, sorts an array in descending order using selection sort
    int temp, largest; // variable used for swapping, holds the element with the max value in the unsorted array
    size_t max_index;  // holds the index of the max element in the unsorted array

    for (size_t i = 0; i < n; ++i)
    {
        largest = arr[i]; // set the largest equal to current element (for comparisons later)
        max_index = i;    // set index of the largest element equal to current element
        // find the largest element;
        for (size_t j = i + 1; j < n; ++j)
        {
            // find the max value in the unsorted array
            if (arr[j] > largest)
            {
                largest = arr[j]; // stores the value of the current found "largest" element value
                max_index = j;    // stores the index of the current found "largest" element value
            }
        }

        // put max value at beginning of the unsorted list
        temp = arr[max_index];
        arr[max_index] = arr[i];
        arr[i] = temp;
    }
}