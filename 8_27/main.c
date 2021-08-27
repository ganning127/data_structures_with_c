#include <stdio.h>
#include <stdlib.h>
void functionPrintArrayInfo(int arr[], int size);

/*

Printing the array in the main() function:
- The entire array's address is the same as the first element in the array's address
- I learned that when you pass an array to another function as an argument, the array actually gets passed as a memory address, not the "entire" array. 
- 

*/

int main(void)
{
    size_t size = 10;

    int arr[size];

    for (size_t counter = 0; counter < size; ++counter)
    {
        arr[counter] = 1 + rand() % (10 + 1 - 1);
    }

    // size of array
    int array_size = sizeof(arr) / sizeof(arr[0]);
    printf("size of array: %d\n", array_size);

    // memory of size address
    printf("address of size of array: %p\n\n", &array_size);

    // adderss of the array itself
    printf("address of the array: %p\n\n", arr);

    // print out address of each element in the array
    printf("address of each element in the array:\n");
    for (size_t i = 0; i < size; ++i)
    {
        printf("element %zu: %p\n", i, &arr[i]);
    }

    functionPrintArrayInfo(arr, size);

    return 0;
}

void functionPrintArrayInfo(int *arr, int size)
{

    printf("\n\nPrinting elements within `functionPrintArrayInfo`\n");

    int array_size = sizeof(*arr) / sizeof(arr[0]);
    printf("size of array: %d\n", array_size);

    // memory of size address
    printf("address of size of array: %p\n\n", &array_size);

    for (size_t x = 0; x < size; x++)
    {
        printf("element %zu: %p \n", x, arr);
        arr++;
    }
}
