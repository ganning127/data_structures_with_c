#include <stdio.h>
#include <stdlib.h>

void selection_sort(int arr[], int n, size_t i);
size_t max_index(int *arr, size_t i);
int random_int(int min, int max);

/*
SELECTION SORT:
    function max_index()
        pass in array and index
        base case: 
            at beg, so return index argument
        otherwise:
            get max_index from rest of array.
            return larger of current index and max_index

    function selection_sort()
        base case:
            at beginning.
        otherwise:
            get max_index of the array before the current index.
            swap currrent index with max_index.
            sort rest of array.
*/

int main()
{
    size_t length = 10; // length of the array
    int arr[length];

    for (size_t i = 0; i < length; ++i)
    {
        arr[i] = random_int(1, 10); // populate array with elements from 1-10
    }

    selection_sort(arr, length, length - 1); // recursive selection sort

    for (size_t i = 0; i < length; ++i)
    {
        printf("%d ", arr[i]); // print the array out
    }
    printf("\n");

    return 0;
}

int random_int(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

size_t max_index(int *arr, size_t i)
{
    // get max index of the elements in subarray arr[0..i]
    if (i == 0)
        return 0;
    size_t max_i = max_index(arr, i - 1);
    if (arr[i] > arr[max_i])
    {
        return i;
    }
    else
    {
        return max_i;
    }
}

void selection_sort(int arr[], int n, size_t i)
{
    if (i == 0) // base case
        return;

    size_t max_i = max_index(arr, i);

    // swap current element and element at max index
    int temp = arr[i];
    arr[i] = arr[max_i];
    arr[max_i] = temp;
    selection_sort(arr, n, i - 1);
}