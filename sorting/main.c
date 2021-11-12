#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void merge_sort(int arr[], size_t length);
void showArray(int arr[], size_t length);
void split_merge(int arr_a[], int arr_b[], size_t length);
void merge(int *listA, int *listB, size_t a_length);
int random_int(int min, int max);
void swap(int arr[], size_t index1, size_t index2);
void putMedianAtBeg(int arr[], size_t length);
void quickSort(int arr[], size_t length);

int main(void)
{
    size_t length = 50;
    // put random numbers in array
    int arr[length];
    for (size_t i = 0; i < length; i++)
    {
        arr[i] = rand() % 100 + 1;
    }

    // show array
    showArray(arr, length);

    // sort array using merge sort
    merge_sort(arr, length);

    puts("");
    // show array
    showArray(arr, length);

    puts("");

    // sort array using quick sort in descending order
    quickSort(arr, length);

    // show array
    showArray(arr, length);
}

void merge_sort(int arr[], size_t length)
{
    // copy arr into another arr_b
    int *arr_b = malloc(sizeof(int) * length);
    for (size_t i = 0; i < length; i++)
        arr_b[i] = arr[i];

    split_merge(arr_b, arr, length); // our actual "mergesort" function
    free(arr_b);                     // free temporary array created
}

void split_merge(int arr_b[], int arr_a[], size_t length)
{
    if (length == 1) // base case
        return;

    size_t middle = length / 2;                                   // middle element to split on (floors the decimal)
    split_merge(arr_a, arr_b, middle);                            // first half
    split_merge(arr_a + middle, arr_b + middle, length - middle); // second half
    merge(arr_b, arr_a, length);                                  // merge the two arrays
}

void showArray(int arr[], size_t length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge(int *listA, int *listB, size_t length)
{
    size_t i = 0;          // index for first half of listA
    size_t j = length / 2; // index for second half of listA
    size_t k = 0;          // index for listB

    while (i < length / 2 && j < length)
    {
        if (listA[i] < listA[j])
        {
            listB[k] = listA[i];
            k++;
            i++;
        }
        else
        {
            listB[k] = listA[j];
            k++;
            j++;
        }
    }

    while (i < length / 2)
    {
        // elements of the first half that have not been added yet
        listB[k] = listA[i];
        k++;
        i++;
    }

    while (j < length)
    {
        // elements of the second half that have not been added yet
        listB[k] = listA[j];
        k++;
        j++;
    }
}

int random_int(int min, int max)
{
    // returns int from [min, max]
    return min + rand() % (max + 1 - min);
}

// quicksort

size_t partitionArray(int arr[], size_t length)
{
    /*
    // j looks for things less  than or equal to the pivot
    // eventually, we just put the pivot where i is
    // i is where you are inseting items when you find an item near the end that is smaler than the pivot
    */

    int pivot = arr[length - 1];
    int i = -1;
    int j = length + 1;
    while (1)
    {
        do
        {
            i++;
        } while (arr[i] > pivot); // not testing for equality against the pivot makes sure that we don't go out of bounds

        do
        {
            j--;
        } while (arr[j] < pivot); // using a do-while loop if the pivots were both at the end

        if (i >= j)
        {
            return j;
        }
        swap(arr, i, j);
    }
}

void quickSort(int arr[], size_t length)
{
    static bool subtracted = false;

    if (!subtracted)
    {
        length--;
        subtracted = true;
    }
    if (length <= 1)
        return;
    putMedianAtBeg(arr, length);
    size_t i = partitionArray(arr, length);
    quickSort(arr, i);
    quickSort(arr + i + 1, length - i - 1);
}

void swap(int arr[], size_t index1, size_t index2)
{
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

void putMedianAtBeg(int arr[], size_t length)
{

    size_t middle = length / 2;
    size_t first = 0;
    size_t last = length - 1;
    // printf("first: %d\n", arr[first]);
    // printf("middle: %d\n", arr[middle]);
    // printf("last: %d\n", arr[last]);

    if (arr[first] > arr[last])
    {
        swap(arr, first, last);
    }
    if (arr[middle] < arr[first])
    {
        swap(arr, middle, last);
    }
    if (arr[first] > arr[last])
    {
        swap(arr, first, last);
    }
}

/*
    Stability: the measure of whther or not hte given inputs stay in the same order

    Ex: input; 5, _, _, 5, _, _, _, 5
    output: would the five's still be in the same order when they are together
        - stability is how well they stay together
*/