#include <stdio.h>
#include <stdlib.h>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(int arr[], int n)
{
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
    }
}

int main(void)
{

    int arr[] = {
        1, 1, 2, 2, 6, 5, 6, 4};

    bubble_sort(arr, 7);

    int max = arr[6];
    int min = arr[0];
    int min_1 = arr[1];

    printf("a: %d\n", min);
    printf("b: %d\n", min_1);
    printf("c: %d\n", max - min - min_1);

    return 0;
}
