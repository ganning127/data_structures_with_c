#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], int n);
void selection_sort(int arr[], int n);

int main(void)
{
    int nums;
    printf("How many numbers do you want? "); // number of elements in array
    scanf("%d", &nums);

    int seed;
    printf("What do you want to seed random as? "); // seed for random to use
    scanf("%d", &seed);

    int min;
    printf("Min value: "); // min value that random can generate
    scanf("%d", &min);

    int max;
    printf("Max value: "); // max value that random can generate
    scanf("%d", &max);

    int arr[nums]; // create array with enough memory for `nums` elements (user specified)

    srand(seed); // seed random

    for (int i = 0; i < nums; ++i)
    {
        // populate array with random numbers
        arr[i] = min + rand() % (max + 1 - min); // random number between [min, max]
    }

    printf("The array before insertion sort in ascending order: ");
    for (int i = 0; i < nums; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    insertion_sort(arr, nums);

    printf("The array after insertion sort in ascending order: ");
    for (int i = 0; i < nums; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    selection_sort(arr, nums);
    printf("\n");

    printf("The array after selection sort in descending order: ");
    selection_sort(arr, nums);
    for (int i = 0; i < nums; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
