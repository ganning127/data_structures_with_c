#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 1;

typedef struct node
{
    int key;
} Node;

typedef struct arraylist
{
    unsigned int capacity; // value
    Node **array;          // array of NodePtr pointers
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
void print_pointers(ArrayList *list);
int main(void)
{
    ArrayList *nu = al_create();

    al_insert(nu, 4);
    al_insert(nu, 3);
    al_insert(nu, 5);
    al_insert(nu, 2);
    al_insert(nu, 6);
    al_insert(nu, 65);
    al_insert(nu, 1);
    // print_pointers(nu);
    print_level_order(nu);

    return 0;
}

void print_pointers(ArrayList *list)
{
    for (size_t i = 0; i < list->capacity; ++i)
        printf("%p ", list->array[i]);

    puts("");
}
void al_insert(ArrayList *list, int key)
{
    // printf("key called: %d\n", key);
    size_t index = 0;
    size_t items = 0;

    // count how many items are in list and resize if necesary

    while (list->array[index] != NULL)
    {
        printf("%p\n", list->array[index]);
        if (key < list->array[index]->key)
        {
            // look at left child
            index = left_child(index);
        }
        else if (key >= list->array[index]->key)
        {
            // look at right child
            index = right_child(index);
        }
        if (index >= list->capacity)
            resize(list, list->capacity);
    }

    // resize(list, list->capacity);
    // printf("insert index: %zu\n", index);
    // insert here
    Node *nu = malloc(sizeof(Node));
    nu->key = key;
    list->array[index] = nu;
}

ArrayList *al_create()
{
    ArrayList *nu = malloc(sizeof(ArrayList)); // allocate memory for the struct itself
    nu->capacity = INITIAL_CAPACITY;

    nu->array = calloc(nu->capacity, sizeof(Node *)); // setting elements in the array to 0

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
    {
        if (array_list->array[i] == NULL)
            printf("NULL ");
        else
            printf("%d ", (array_list->array[i])->key);
    }
    printf("\n");
}

void resize(ArrayList *list, unsigned int old_capacity)
{
    list->capacity = old_capacity * 2 + 1;
    list->array = realloc(list->array, list->capacity * sizeof(Node *)); // `capacity` is like the number of elements. we need to multiply by the sizeof(int) to get the true number of bytes that need to be allocateted

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