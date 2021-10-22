#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 1;
typedef struct arraylist
{
    unsigned int capacity; // value
    int *array;            // pointer to the next element
} ArrayList;
// it should be an array of struct pointers
// each struct should contain key
ArrayList *al_create();
void al_destroy(ArrayList **listPtr);
void al_print(ArrayList *list);
void resize(ArrayList *list, unsigned int old_capacity);
void al_insert(ArrayList *list, int key);
void al_delete(ArrayList *list, int key);

size_t left_child(size_t index);
size_t right_child(size_t index);
size_t parent_index(size_t index);
void print_level_order(ArrayList *array_list);

int main(void)
{
    ArrayList *nu = al_create();
    al_insert(nu, 4);
    al_insert(nu, 3);
    al_insert(nu, 5);
    al_insert(nu, 2);
    al_insert(nu, 6);

    return 0;
}

void al_insert(ArrayList *list, int key)
{
    size_t i = 0;
    // for (i = list->capacity++; i > 0 && list->array[i - 1] > key; --i)
    // {
    //     // similar to insertion sort
    //     // list->array[i - 1] > key, then list->array[i - 1] needs to be shifted towards the end by 1
    //     list->array[i] = list->array[i - 1];
    // }

    while (list->array[i] != '\0')
    {
        if (key < list->array[i])
        {
            // insert to the left of current node
            i = right_child(0);
        }
        else
        {
            // insert to the right of the current node
        }
    }
}

ArrayList *al_create()
{
    ArrayList *nu = malloc(sizeof(ArrayList)); // allocate memory for the struct itself
    nu->capacity = INITIAL_CAPACITY;

    nu->array = malloc(nu->capacity * sizeof(int)); // setting elements in the array to 0

    for (size_t i = 0; i < nu->capacity; ++i)
    {
        nu->array[i] = '\0';
    }

    return nu;
}

size_t left_child(size_t index) { return 2 * index + 1; }
size_t right_child(size_t index) { return 2 * index + 2; }
size_t parent_index(size_t index)
{
    if (index % 2 == 1)
        return (index - 1) / 2;

    return (index - 2) / 2;
}

void print_level_order(ArrayList *array_list)
{
    for (size_t i = 0; i < array_list->capacity; ++i)
        printf("%d ", array_list->array[i]);
    printf("\n");
}

void resize(ArrayList *list, unsigned int old_capacity)
{
    list->capacity = old_capacity * 2 + 1;
    list->array = realloc(list->array, list->capacity * sizeof(int)); // `capacity` is like the number of elements. we need to multiply by the sizeof(int) to get the true number of bytes that need to be allocateted

    // realloc takes a pointer to existting allocated memory, and resizes it
}
/*
    Implementation: Store nodes of the binary stree in level order in the arraylist

    capacity: 2^depth - 1
    left(index): 2(index) + 1
    right(index): 2(index) + 2
    parent(index):
        if (index % 2 == 1)
            parent_index = (index-1) / 2
        else if (index % 2 == 0)
            parent_index = (index-2) / 2

    we resize bst when we need to add another depth

    new_capacity(old_capacity): 2*old_capacity + 1
*/