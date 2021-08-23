#include <stdlib.h>

void selection_sort(int arr[], size_t n)
{
    // this function, `selection_sort()`, sorts an array in descending order using selection sort
    size_t max_index; // `max_index` - holds the index of the maximum element in the array
    int temp;         // `temp` holds a value in the array and is used for swapping

    for (size_t i = 0; i < n; ++i)
    {
        max_index = i; // set max_index equal to first 'unsorted' element in array
        for (size_t j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[max_index])
            {
                max_index = j; // if the current element is larger than the max_index element, set max_index to the current element's index
            }
        }

        // swap values
        temp = arr[max_index];   // set temp equal to max value found
        arr[max_index] = arr[i]; // swap the index of the old max value with the first element in the unsorted array
        arr[i] = temp;           // set the first element in the unsorted array equal to the max value found (desc order)
    }
}