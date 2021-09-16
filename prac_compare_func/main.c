#include <stdio.h>
#include <stdlib.h>

int ascending(const void *const a, const void *const b);

int descending(const void *const a, const void *const b);

void showArray(int arr[], size_t size);

int main(void)
{
    int arr[] = {42, 6, 0, 1, 4, 3, 2, 7, 16};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, n, sizeof(arr[0]), &ascending);
    showArray(arr, n);
    return 0;
}

int ascending(const void *const a, const void *const b)
{
    // `void` is a generic pointer, but we need to cast to use it
    return (*(int *)a - *(int *)b); // qsort does something different if this returns neg, 0, or pos
}

int descending(const void *const a, const void *const b)
{
    return (*(int *)b - *(int *)a);
}

void showArray(int arr[], size_t size)
{
    // prints the array to screen
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}