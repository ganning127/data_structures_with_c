#include <stdlib.h>
#include <stdio.h>

/*
Pointer to variables
 - Both the value of the pointer and the variable that the pointer is pointing to can be changed
 
Pointer to const variable
 - Value of pointer CANNOT be changed
 - Variable that the pointer is pointing to can be changed
 - Why? Since the pointer to pointing to a constant variable, the variable's value cannot be modified. However, since the pointer itself is not constant, it can still point to a different variable.

Const pointer to var
 - Value of pointer can be changed
 - Variable value that the pointer is pointing to CANNOT be changed
 - Why? Since the pointer itself is constant, it cannot point to a differnt variable than from the one which it is declared to point to. However, since the pointer variable's value is not const, then we can still change the value stored in that memory address

Const pointer to const var
 - Value of pointer CANNOT be changed
 - Variable value that the pointer is pointing to CANNOT be changed
 - Why? Since the pointer is constant, it cannot point to a differnt variable than from the one which it is declared to point to. Additionally, since the pointer to pointing to a constant variable, the variable's value cannot be modified

*/

void change_values(int *pointer_to_int, int const *pointer_to_const_int, const int *const_pointer_to_int, const int *const_pointer_to_const_int);

int main(void)
{
    int x = 0;
    int *pointer_to_int = &x;

    const int const_x = 1;
    int const *pointer_to_const_int = &const_x;
    // int *pointer_to_const_int = &const_x; // gives a warning, saying that qualifiers are discarded because the pointer is not a constant, but the value that the pointer is pointing to IS const
    const int *const_pointer_to_int = &x;
    const int *const_pointer_to_const_int = &const_x;
    change_values(pointer_to_int, pointer_to_const_int, const_pointer_to_int, const_pointer_to_const_int);
    return 0;
}

void change_values(int *pointer_to_int, int const *pointer_to_const_int, const int *const_pointer_to_int, const int *const_pointer_to_const_int)
{
    // change value of pointer
    pointer_to_int++;
    pointer_to_const_int++;
    const_pointer_to_int++;
    const_pointer_to_const_int++;

    // change value of int
    (*pointer_to_int)++;
    // (*pointer_to_const_int)++; // pointers to const ints cannot be modified
    // (*const_pointer_to_int)++; // const pointers cannot be modified
    // (*const_pointer_to_const_int)++; // const pointers cannot be modified
};