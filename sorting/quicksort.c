#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    return 0;
}

/*

QuickSort()
    1. Take three random elements, and take the median of those three elements as the pivot.
    2. Put that median in the center of the array.
    3. Partition the array into two parts, one with elements less than the pivot, one with elements greater than the pivot
    4. Call QuickSort() on each half
    Choose another pivot in the middle of the two parts again
*/