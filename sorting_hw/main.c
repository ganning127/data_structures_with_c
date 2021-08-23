#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], size_t n); // change int n to size n
void selection_sort(int arr[], size_t n);
void show(int arr[], size_t n);

int main(void)
{
    size_t nums;
    printf("How many numbers do you want? "); // number of elements in array
    scanf("%zu", &nums);

    int seed;
    printf("What do you want to seed random as? "); // seed for random to use
    scanf("%d", &seed);

    int min;
    printf("Min value: "); // min value that random can generate
    scanf("%d", &min);

    int max;
    printf("Max value: "); // max value that random can generate
    scanf("%d", &max);

    int arr[nums]; // create array with elements of integer type and with enough memory for `nums` elements (user specified)

    srand(seed); // seed random

    for (size_t i = 0; i < nums; ++i)
    {
        // populate array with random numbers
        arr[i] = min + rand() % (max + 1 - min); // random number between [min, max]
    }

    printf("\n");

    printf("The array before any sorting: ");
    show(arr, nums);

    printf("\n");

    insertion_sort(arr, nums);
    printf("The array after insertion sort in ascending order: ");
    show(arr, nums);

    printf("\n");

    selection_sort(arr, nums);
    printf("The array after selection sort in descending order: ");
    show(arr, nums);
    return 0;
}

void show(int arr[], size_t n)
{
    // function prints arrays out on single line
    for (size_t i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}