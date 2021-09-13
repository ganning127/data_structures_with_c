#include <stdio.h>
#include <stdlib.h>
#define ARR_LENGTH 100
#define MAX_NUM 100

void selection_sort(int arr[], int n, size_t i);
void insertion_sort(int arr[], size_t i);
void insert(int arr[], size_t i);
size_t max_index(int *arr, size_t i);
int random_int(int min, int max);
void fillArray(int arr[], size_t length);
void showArr(int arr[], size_t length);
double getMedian(int arr[], size_t length);
void showMode(int arr[], size_t length);
double getAverage(int arr[], size_t length);

int main()
{
    int arr[ARR_LENGTH]; // initialize array with ARR_LENGTH
    srand(42);           // seed random

    fillArray(arr, ARR_LENGTH); // fills the array

    printf("Before any sorting\n");
    showArr(arr, ARR_LENGTH); // prints array on screen

    printf("\n");

    selection_sort(arr, ARR_LENGTH, ARR_LENGTH - 1); // recursive selection sort
    printf("After selection sort in ascending order\n");
    showArr(arr, ARR_LENGTH);

    // analysis
    double median = getMedian(arr, ARR_LENGTH); // median of array
    double avg = getAverage(arr, ARR_LENGTH);   // averge of all elements in array

    printf("\n");

    insertion_sort(arr, ARR_LENGTH - 1); // recursive insertion sort
    printf("After insertion sort in descending order\n");
    showArr(arr, ARR_LENGTH);

    printf("\n");
    printf("Mean: %.1lf\n", avg);
    printf("Median: %.1f\n", median);
    showMode(arr, ARR_LENGTH);
    return 0;
}

void showMode(int arr[], size_t length)
{
    // prints out the mode of arr[]
    int counts[MAX_NUM + 1];
    // populate array with zeros
    for (size_t j = 0; j < MAX_NUM + 1; ++j)
    {
        counts[j] = 0;
    }

    for (size_t i = 0; i < length; ++i)
    {
        ++counts[arr[i]]; // increment the count of the index (value of element is index)
    }

    // find the max element in the counts array
    int max_index = 0;
    for (size_t z = 0; z < MAX_NUM + 1; ++z)
    {
        if (counts[z] > counts[max_index])
            max_index = z;
    }

    // loop through all elements in the array and print elements with values >= max_index
    printf("Mode: ");
    for (size_t f = 0; f < MAX_NUM + 1; ++f)
    {
        if (counts[f] >= counts[max_index])
            printf("%zu ", f);
    }
    printf("\n");
}

double getAverage(int arr[], size_t length)
{
    // returns the average of all elemets in arr[]
    int sum = 0;

    for (size_t i = 0; i < length; ++i)
    {
        sum += arr[i];
    }

    double avg = (double)sum / ARR_LENGTH;

    return avg;
}

double getMedian(int arr[], size_t length)
{
    // returns the median element in arr[]
    double median = 0;

    // if number of elements are even
    if (length % 2 == 0)
        median = (arr[(length - 1) / 2] + arr[length / 2]) / 2.0;
    // if number of elements are odd
    else
        median = arr[length / 2];

    return median;
}

void fillArray(int arr[], size_t length)
{
    // fills array with random nunbers from [0, MAX_NUM]
    for (size_t i = 0; i < length; ++i)
    {
        arr[i] = random_int(0, MAX_NUM);
    }
}

void showArr(int arr[], size_t length)
{
    // prints out the array with a newline at the end
    for (size_t i = 0; i < length; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int random_int(int min, int max)
{
    // returns num from [min, max]
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
    // recursively sort arr[] using selection sort
    if (i == 0) // base case
        return;

    size_t max_i = max_index(arr, i);

    // swap current element and element at max index
    int temp = arr[i];
    arr[i] = arr[max_i];
    arr[max_i] = temp;
    selection_sort(arr, n, i - 1);
}

void insert(int arr[], size_t i)
{
    // inserts the maximum element of the unsorted array recursively
    if (i == 0)
        return;

    if (arr[i] > arr[i - 1])
    {
        int temp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = temp;
    }

    insert(arr, i - 1);
}

void insertion_sort(int arr[], size_t i)
{
    // insertion sort in descending order
    if (i == 0)
        return;

    insertion_sort(arr, i - 1);

    insert(arr, i);
}

/*
pseudocode
    function insert()
        base case: 
            at index 0, just use return; (no value)
        otherwise: 
            compare to prev element, and swap if necessary.
            recursive function call on array and index-1

    function insertion_sort()
        **start at end of the array (pass in size)
        base_case:
            at the beginning, juse use return; (no value)
        otherwise:
            recursive function call on array and index-1
            insert current index into sorted array using insert()
*/