#include <stdio.h>

int main(void)
{

    return 0;
}

/*
    Insertion Sort
    1. Assume that everything before current index is sorted.
    2. Find min element
    3. Place min element at the start of the current index

    Recursive
    Two parts
    Actually sorting an element at the end into the sorted array before it
        Base case: at beginning or prev eleement is smaller
        otherwise:
            swap with previous element
            call function again on array and size-1
    Iterate through the elements of the array
        Use static variable to keep track of which index we are looking at (static int index = 1)
        Base case: no more elements
        otherwise: 
            call halper function
            increment index
            call this function again on array and size
*/

/*
    Selection Sort
    Two parts
    One function goes through the unsorted array
        Iterate through elements
    One function that finds the minninum index recursively of the unsorted array
        base case:
            when we get to end of array (no more elements)
        otherwise:
            compare value at min index to current indexs

*/