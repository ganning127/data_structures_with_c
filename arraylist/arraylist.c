#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 8

typedef struct arraylist
{
    int *array;      // declared as pointer so we don't need to specify size
    size_t size;     // how many elements its currently holding
    size_t capacity; // how many elements it can hold
} ArrayList;

ArrayList *al_create();
void al_destroy(ArrayList **listPtr);
void al_print(ArrayList *list);
void resize_if_full(ArrayList *list);
void al_insert(ArrayList *list, int key);
void al_delete(ArrayList *list, int key);

int main(void)
{
    ArrayList *nu = al_create();

    al_insert(nu, 4);
    al_insert(nu, 6);
    al_insert(nu, 10);
    al_insert(nu, 1);
    al_insert(nu, -35);

    al_delete(nu, 1);

    for (int i = 0; i < 100; ++i)
        al_insert(nu, i);
    printf("size: %zu \ncapacity: %zu\n", nu->size, nu->capacity);
    al_print(nu);
    al_destroy(&nu);

    printf("%p\n", nu);
    return 0;
}

void al_insert(ArrayList *list, int key)
{
    resize_if_full(list);
    size_t i;
    for (i = list->size++; i > 0 && list->array[i - 1] > key; --i)
    {
        // similar to insertion sort
        // list->array[i - 1] > key, then list->array[i - 1] needs to be shifted towards the end by 1
        list->array[i] = list->array[i - 1];
    }
    list->array[i] = key;
}

void al_delete(ArrayList *list, int key)
{
    /*
        look from the front     
        once we find it, start shifting things behind the item found

        starting from front will make one full pass of the array
    */
    size_t i = 0;
    for (; i < list->size && key != list->array[i]; ++i)
    {
    } // for loop does seraching for us, we don't need a body
    // at this point, i is at the size or at the first instance of the key

    for (; i < list->size - 1 && list->array[i + 1] == key; ++i)
    {
    }
    // at the point, i is at size, or at last instance of key

    for (; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];

    if (i == list->size - 1)
        --list->size;

    printf("index: %zu\n", i);
}

void resize_if_full(ArrayList *list)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(int)); // `capacity` is like the number of elements. we need to multiply by the sizeof(int) to get the true number of bytes that need to be allocateted

        // realloc takes a pointer to existting allocated memory, and resizes it
    }
}

void al_destroy(ArrayList **listPtr)
{
    // constant time, very fast
    ArrayList *list = *listPtr;
    free(list->array);
    free(list);
    *listPtr = NULL; // since the array has been free'd, set its pionter to null
}

void al_print(ArrayList *list)
{
    for (size_t i = 0; i < list->size; ++i)
    {
        printf("%d, ", list->array[i]);
    }
    puts("");
}

ArrayList *al_create()
{
    ArrayList *nu = malloc(sizeof(ArrayList)); // allocate memory for the struct itself
    nu->size = 0;
    nu->capacity = INITIAL_CAPACITY;

    nu->array = calloc(nu->capacity, sizeof(int)); // setting elements in the array to 0
    /*
        calloc = malloc, but sets all elements equal to zero
    */

    return nu;
}