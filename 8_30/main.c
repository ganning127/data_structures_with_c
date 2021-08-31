#include <stdio.h>

void fun(int arr[], size_t n);

int main(void)
{

    // size_t n = 5;
    // int arr[n];
    // printf("&n: %p\n", &n);
    // printf("arr: %p\n", arr);
    // printf("&arr: %p\n", &arr);
    // printf("&arr[0]: %p\n", &arr[0]);
    // printf("&arr[0]: %p\n", &arr[1]); // elements of an array are sequentially together in memory
    // puts("function call");

    // fun(arr, n);
    return 0;
}

/*
    Insertion Sort
    1. Assume that everything before current index is sorted.
    2. Find min element
    3. Place min element at the start of the current index

    Recursive
    Two parts
    - Actually sorting an element at the end into the sorted array before it
        Base case: at beginning or prev eleement is smaller
        otherwise:
            swap with previous element
            call function again on array and size-1

*/

// void fun(int arr[], size_t n)
// {
//     printf("&n: %p\n", &n);
//     printf("arr: %p\n", arr);
//     printf("&arr: %p\n", &arr); // a pointer to a pointer
//     printf("&arr[0]: %p\n", &arr[0]);
// }