#include <stdio.h>
#include <stdlib.h>
void functionPrintArrayInfo(int arr[], size_t size);

/*

Output:
array: 5 4 10 4 7 2 2 1 1 6 

Printing elements within `main()`
size of array: 10
address of size of array: 0x7ffee947f824
address of the array: 0x7ffee947f7c0
address of first element in the array: 0x7ffee947f7c0
value of the array: 5


Printing elements within `functionPrintArrayInfo()`
size of array: 10
address of size of array: 0x7ffee947f7a0
address of the array: 0x7ffee947f7c0
address of first element in the array: 0x7ffee947f7c0
value of the array: 5

Things I learned
- The array's memory address is the same as the first element in the array's address
- In the `functionPrintArrayInfo()` function, when we print the value of the array by using `*arr`, we get the value of the first element in the array because the memory address of the array is the same as the memory address of the first element's address 
- Array elements are stored in consecutive memory locations 
- When you pass an array to another function as an argument, the array actually gets passed as a memory address, not the "entire" array value 
- The address that is passed as an argument is the address of the first element in the array
- Printing the value of the array just prints the first element in the array
- The memory address of the array passed from the `main()` function to the `functionPrintArrayInfo()` is the same in both 
- The memory address of the size of the array is different because passing the size paramter is pass by value, so a copy is made and sent to the `functionPrintArrayInfo()` function
- The value of the `size` paramter is the same as in the `main()` function

*/

int main(void)
{
    srand(42);
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

void functionPrintArrayInfo(int arr[], size_t size)
{
    printf("\n\nPrinting elements within `functionPrintArrayInfo()`\n");

    printf("size of array: %zu\n", size);

    // memory of size address
    printf("address of size of array: %p\n", &size);

    // adderss of the array itself
    printf("address of the array: %p\n", arr);

    printf("address of first element in the array: %p\n", &arr[0]);
    printf("value of the array: %d\n", *arr);
}
