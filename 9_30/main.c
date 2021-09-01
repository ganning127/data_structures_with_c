#include <stdio.h>
#include <string.h>

void print_size_of(int arr[], int i);
void func(size_t rows, size_t cols, int arr[][cols]);
void pass_by_ref(int *aptr, int b);

int main(void)
{
    // char chr_arr[5] = {
    //     'h', 'e', 'l', 'l', 'o'};

    // char string1[] = "hello"; // automatically has a `null` character appended to it

    // string1[3] = 0; // ending the array earlier
    // printf("length of string1: %zu\n", strlen(string1));
    // printf("length of chr_arr: %zu\n", sizeof(chr_arr));

    // puts(string1);

    // printf("%d\n", string1[5]);
    // puts("");
    // int i, arr[10];

    // printf("size of arr: %zu\n", sizeof(arr));
    // printf("size of i: %zu\n", sizeof(i));

    // print_size_of(arr, i);

    //     int b[2][3] = {
    //         {1, 2, 3},
    //         {4, 5, 6}};
    //     // arr[rows][cols]
    //     int b_one[6];

    //     int c[2][3] = {{1, 2}, 4, 5, 6}; // c already knows how many rows and columns there are
    //                                      // { } is treated as row 0
    //     // int c[2][2] = {}; // sets all elements in array to zero
    //     printf("element: %d\n", c[0][1]);

    //     printf("size of c: %zu\n", sizeof(b)); // 6 integers of 4 bytes each (outputs: 24)

    int x = 6;

    int *xptr = &x; // memory address of x
    int y = *xptr;

    int **xptrptr = &xptr;

    printf("pointer to x: %p\n", xptr);
    printf("value of xptr: %d\n", *xptr); // retrives the value from the xptr memory address
    // `*` is the dereferencing operator

    printf("pointer to xptr: %p\n", xptrptr);
    printf("value of xptrptr: %p\n", *xptrptr);

    printf("value of y: %d\n", y);

    int b = 10;

    printf("value x: %d\n", x);
    printf("y: %d\n", y);

    pass_by_ref(&x, y);
    printf("value x: %d\n", x);
    printf("y: %d\n", y);
    return 0;
}

// void print_size_of(int arr[], int i)
// {
//     printf("in function...\n");
//     printf("size of arr: %zu\n", sizeof(arr)); // arr is a pointer (8 bytes for a pointer on a 64bit machine)
//     printf("size of i: %zu\n", sizeof(i));     // we always pass in how long the array is, because if we don't, we won't have any way of knowing how long the array is

//     int arr2[10];

//     printf("size of arr2: %zu\n", sizeof(arr2));
// }
void pass_by_ref(int *aptr, int b)
{
    ++b;
    ++(*aptr); // will change the memory address
};

void func(size_t rows, size_t cols, int arr[][cols])
{
    // with 2-D arrays, you need to specify one dimension
    // for an n-D array, you need to provide n-1 dimensions
}

void insertion_sort(int arr[], size_t size)
{
    static int start_index = 0;
}

/*
    Insertion Sort
    1. Assume that everything before current index is sorted.
    2. Find min element
    3. Place min element at the start of the current index

    Recursive
    Two parts
    Actually sorting an element at the end into the sorted array before it
        Base case: 
            at beginning or prev eleement is smaller
        otherwise:
            swap with previous element
            call function again on array and size-1
    Iterate through the elements of the array
        Use static variable to keep track of which index we are looking at (static int index = 1)
        Base case: 
            no more elements
            set index to 1
        otherwise: 
            call halper function
            increment index
            call this function again on array and size
*/

/*
    Selection Sort
    Two parts
    One function goes through the unsorted array
        static int start_index = 0, increment start_index every round for unsorted array
        Iterate through elements
    One function that finds the minninum index recursively of the unsorted array 
        static min_index;
        base case:
            when we get to end of array (no more elements)

            return min_index
        otherwise:
            compare value at min index to current index
            swap the element at min index and current index
            call again on array, next index, and size
    Another function to do the sorting
        base case:
            no more elements
        otherwise:
            ssssssss

*/