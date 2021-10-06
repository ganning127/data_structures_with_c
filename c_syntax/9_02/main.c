#include <stdio.h>

int main(void)
{
    int x = 5;
    int *xptr = &x;

    int a[] = {
        6,
        42,
        2,
        0,
        1,
        3,
        4};

    int *b = a;

    char c = '\0';
    char *cptr = &c;

    printf("value of (c): %p\n", cptr);
    printf("value of (a): %p\n", a); // treat array as pointer and add / sub as we need to in order to index from arrays

    printf("value of (c+1): %p\n", cptr + 1); // adds 1 b/c a char is 1 byte wide
    printf("value of (a+1): %p\n", a + 1);    // adds 4 b/c int is 4 bytes wide

    x = 2 + (2 << 9) + (2 << 17) + (2 >> 25); // 2**9, 2**17, 2*25, +2
    cptr = (char *)xptr;                      // allows us to read the integer one byte at a time

    printf("deref char pointer: %d\n", *(cptr + 2));

    printf("x: %d\n", x);
    return 0;
}

/*
Guide to recursive sorting

INSERTION SORT:
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
            insert current index into sorted array using insert().
            decrement static index
    
SELECTION SORT:
    function max_index()
        pass in array and index
        base case: 
            at beg, so return index argument
        otherwise:
            ignore current index and get max_index from rest of array.
            return smaller of current index and max_index

    function selection_sort()
        base case:
            at beginning.
        otherwise:
            get max_index of the array before the current index.
            swap currrent index with max_index.
            sort rest of array.
*/