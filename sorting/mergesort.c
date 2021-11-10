#include <stdio.h>
#include <stdlib.h>

void merge_sort(int arr[], size_t length);
void showArray(int arr[], size_t length);
void split_merge(int arr_a[], int arr_b[], size_t length);
void merge(int *listA, int *listB, size_t a_length);
int random_int(int min, int max);

int main(void)
{
    size_t length = 23;
    int arr[length];
    for (size_t i = 0; i < length; i++)
        arr[i] = random_int(0, 100); // random number to populate array

    printf("original array: \n");
    showArray(arr, length);

    puts("");
    merge_sort(arr, length);

    printf("sorted array: \n");
    showArray(arr, length);

    return 0;
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
/*
MergeSort():
    1. Copy A -> B;
    2. SplitMerge(B into A);

SplitMerge(B, A, whatever indexes):
    - SplitMerge(A1, B1) // sorting the halves of A into B and then mergeing B into A??? first half of a and first half of b are now sorted
    - SplitMerge(A2, B2)
    - Merge (B into A) // takes in two arrays and merges some parts of the first array into the second array
    // no need to return anything from merge()

    https://www.geeksforgeeks.org/merge-one-array-of-size-n-into-another-one-of-size-mn/
*/