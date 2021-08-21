#include <stdio.h>
#include <stdlib.h>

void selection_sort(int arr[], int n);

int main(void)
{
    int arr[] = {10, 9, 2, 8, 12, 45, 124};

    int n = sizeof arr / sizeof arr[0];
    ;

    selection_sort(arr, n);
    return 0;
}
