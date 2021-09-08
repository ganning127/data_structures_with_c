#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    return 0;
}

/*
BINARY SEARCH:
    *don't need min and max index*
    pass in array, size, target
    Check middle
    if not value:
        call again on either (array and size/2)or (array+size/2 and size/2)
    else:
        return index
*/