#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int a[], int n); // tells compiler func exists, returns, args
int main_8_19(void);
void grade_average(void);
// don't define functions above main, so use func prototype (above)
int main(void) // there always needs to be a main function, we always need to have `void` if there are no args
{
    printf("%c\n", 'A');
    printf("%d\n", 'A');

    int x = 0;
    // ++x;

    printf("x is: %d\n", ++x);
    // x++;

    printf("x is: %d\n", x++);

    /*
    srand(42); // seeds random
    int n = 100;
    int nums[n];

    for (int i = 0; i < n; i++)
    {
        nums[i] = rand() % 101; // nums from 0 - 100
        // printf("%d ", nums[i]);
    }
    // printf("\nOrganized\n");
    bubble_sort(nums, n);

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d ", nums[i]);
    // }

    printf("\n");

    
    */

    // main_8_19();
    // grade_average();
    return 0;
}
