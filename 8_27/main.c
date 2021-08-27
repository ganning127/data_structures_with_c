#include <stdio.h>
#include <stdlib.h>
void functionPrintArrayInfo(int *arr, size_t size);

/*

Output:
array: 8 10 4 9 1 3 5 9 4 10 

Printing elements within `main()`
size of array: 10
address of size of array: 0x7ffee66f7824
address of the array: 0x7ffee66f77c0
address of first element in the array: 0x7ffee66f77c0
value of the array: 8


Printing elements within `functionPrintArrayInfo()`
size of array: 1
address of size of array: 0x7ffee66f779c
address of the array: 0x7ffee66f77c0
address of first element in the array: 0x7ffee66f77c0
value of the array: 8

- The size of the array in `main()` is accurate, which is 10, but the size of the array when printed in `functionPrintArrayInfo()` gives a value of 1. This is because the memory address of the first element in the array is passed to the function, not the “entire” array itself
- The memory addresses of the arrays when printed in the two functions are the same, so arrays are passed by memory addresses

Things I learned
- The entire array's memory address is the same as the first element in the array's address
- Array elements are stored in consecutive memory locations 
- When you pass an array to another function as an argument, the array actually gets passed as a memory address, not the "entire" array value 
- That's why when getting the array size by using *arr in the `functionPrintArrayInfo()` function, the size is 1 because the address is the first element in the array
- The address that is passed as an argument is the address of the first element in the array
- Printing the value of the array just prints the first element in the array
- To print multiple elements in the array from the function, we need to increment the pointer to the array by using ++arr
- The memory address of the array passed from the `main()` function to the `functionPrintArrayInfo()` is the same in both 
- To achieve the same output in the `functionPrintArrayInfo()` function as in `main()`, I needed to set the `arr` argument as a pointer type


*/

int main(void)
{

    size_t size = 10; // 10 elements in array

    int arr[size]; // initialize array

    for (size_t counter = 0; counter < size; ++counter)
    {
        arr[counter] = 1 + rand() % (10 + 1 - 1); // random elements from 1-10
    }

    printf("array: ");
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]); // print out the array at the beginning
    }

    printf("\n\nPrinting elements within `main()`\n");

    // size of array
    int array_size = sizeof(arr) / sizeof(arr[0]);
    printf("size of array: %d\n", array_size); // size of the array

    // memory of size address
    printf("address of size of array: %p\n", &array_size); // memory address of the size

    // adderss of the array itself
    printf("address of the array: %p\n", arr); // memory address of the array

    // print out address of each element in the array
    printf("address of first element in the array: %p\n", &arr[0]); // memory address of the first element in the array

    // print value of the array
    printf("value of the array: %d\n", *arr); // value of the array

    functionPrintArrayInfo(arr, size);

    return 0;
}

void functionPrintArrayInfo(int *arr, size_t size)
{
    printf("\n\nPrinting elements within `functionPrintArrayInfo()`\n");

    int array_size = sizeof(*arr) / sizeof(arr[0]);
    printf("size of array: %d\n", array_size);

    // memory of size address
    printf("address of size of array: %p\n", &array_size);

    // adderss of the array itself
    printf("address of the array: %p\n", arr);

    printf("address of first element in the array: %p\n", &arr[0]);
    printf("value of the array: %d\n", *arr);
}
