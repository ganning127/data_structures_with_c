#include <stdio.h>
#include <stdlib.h>

void selection_sort(int arr[], int n, size_t i);

int random_int(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

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
// get max index of the elements in subarray arr[0..i), i.e., from arr[0] to arr[i - 1]
size_t max_index(int *arr, size_t i)
{
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

int main()
{
    size_t length = 10;
    int arr[4] = {1, 9, 96, 4};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);

    size_t max_i = max_index(arr, arr_len - 1);
    printf("max index; %zu\n", max_i);
    // for (size_t j = 0; j < length; ++j)
    // {
    //     arr[j] = random_int(1, 10); // populate array
    // }

    // selection_sort(arr, 4, 0);

    // for (size_t i = 0; i < 4; ++i)
    // {
    //     printf("%d ", arr[i]);
    // }

    printf("\n");

    return 0;
}

// void selection_sort(int arr[], int n, size_t i)
// {
//     if (i == 0)
//     {
//         return;
//     }

//     size_t max_i = max_index(arr, n, 0);
//     printf("max index; %zu\n", max_i);
// }
