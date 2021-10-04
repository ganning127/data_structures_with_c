#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 8

typedef struct arraylist
{
    int *array;      // declared as pointer so we don't need to specify size
    size_t size;     // how many elements its currently holding
    size_t capacity; // how many elements it can hold
} ArrayList;

void resize_if_full(ArrayList *list);
void s_print(ArrayList *list);
ArrayList *al_create();
void s_push(ArrayList *list, int key);
void s_pop(ArrayList *list);
int s_peek(ArrayList *list);
void s_destroy(ArrayList **listPtr);
void showArray(int arr[], size_t size)
{
    // prints the array to screen
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main(void)
{
    ArrayList *nu = al_create();
    s_push(nu, 1);
    s_push(nu, 2);
    s_push(nu, 3);
    s_pop(nu);

    printf("peeking: %d\n", s_peek(nu));
    s_print(nu);

    s_destroy(&nu);
}

int s_peek(ArrayList *list)
{
    return list->array[0];
}

void s_pop(ArrayList *list)
{
    // removes the head
    for (size_t i = 0; i < list->size; ++i)
    {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
}

void s_push(ArrayList *list, int key)
{
    resize_if_full(list);
    size_t i;
    for (i = list->size++; i > 0; --i)
    {
        // shifts all elements towards the end by 1 index;
        list->array[i] = list->array[i - 1];
    }
    list->array[0] = key;
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

void s_print(ArrayList *list)
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

void s_destroy(ArrayList **listPtr)
{
    // constant time, very fast
    ArrayList *list = *listPtr;
    free(list->array);
    free(list);
    *listPtr = NULL; // since the array has been free'd, set its pionter to null
}