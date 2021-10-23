#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 1;

typedef struct node
{
    int key;
    size_t index; // index number in the arraylist
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

void al_delete(ArrayList *list, int key);

size_t bst_left_child(size_t index);
size_t bst_right_child(size_t index);
size_t parent_index(size_t index);
void bst_print_level_order(ArrayList *array_list);
void bst_print_in_order(ArrayList *array_list);
void print_pointers(ArrayList *list);
void bst_resize(ArrayList *list, unsigned int old_capacity);
void bst_insert(ArrayList *list, int key);

// stack stuff

typedef struct stack
{
    Node **array;    // declared as pointer so we don't need to specify size
    size_t size;     // how many elements its currently holding
    size_t capacity; // how many elements it can hold
} Stack;
typedef Stack *StackPtr;

void resize_if_full(StackPtr list);
StackPtr create();
void push(StackPtr stack, Node *c);
void print(StackPtr stack);
Node *pop(StackPtr stack);
Node *peek(StackPtr stack);
void clear(StackPtr stack);

int main(void)
{
    ArrayList *nu = al_create();

    bst_insert(nu, 4);
    bst_insert(nu, 3);
    bst_insert(nu, 5);
    bst_insert(nu, 2);
    bst_insert(nu, 6);
    print_pointers(nu);
    // bst_print_level_order(nu);
    bst_print_in_order(nu);

    return 0;
}

void bst_in_order_helper(ArrayList *array_list, Node *node)
{
    if (node == NULL)
    {
        return;
    }
    size_t left_index = bst_left_child(node->index);
    size_t right_index = bst_right_child(node->index);

    if (left_index < array_list->capacity)
        bst_in_order_helper(array_list, array_list->array[left_index]);

    printf("%d ", node->key);

    if (right_index < array_list->capacity)
        bst_in_order_helper(array_list, array_list->array[right_index]);
}

void bst_print_in_order(ArrayList *array_list)
{
    bst_in_order_helper(array_list, array_list->array[0]);
    puts("");
}

void print_pointers(ArrayList *list)
{
    for (size_t i = 0; i < list->capacity; ++i)
        printf("%p ", list->array[i]);

    puts("");
}
void bst_insert(ArrayList *list, int key)
{
    // printf("key called: %d\n", key);
    size_t index = 0;

    while (list->array[index] != NULL)
    {
        if (key < list->array[index]->key)
        {
            // look at left child
            index = bst_left_child(index);
        }
        else if (key >= list->array[index]->key)
        {
            // look at right child
            index = bst_right_child(index);
        }
        if (index >= list->capacity)
            bst_resize(list, list->capacity);
    }

    // printf("insert index: %zu\n", index);
    // insert here
    Node *nu = malloc(sizeof(Node));
    nu->key = key;
    nu->index = index;
    list->array[index] = nu;
}

ArrayList *al_create()
{
    ArrayList *nu = malloc(sizeof(ArrayList)); // allocate memory for the struct itself
    nu->capacity = INITIAL_CAPACITY;

    nu->array = calloc(nu->capacity, sizeof(Node *)); // setting elements in the array to 0

    return nu;
}

size_t bst_left_child(size_t index) { return 2 * index + 1; }
size_t bst_right_child(size_t index) { return 2 * index + 2; }
size_t parent_index(size_t index)
{
    if (index % 2 == 1)
        return (index - 1) / 2;

    return (index - 2) / 2;
}

void bst_print_level_order(ArrayList *array_list)
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

void bst_resize(ArrayList *list, unsigned int old_capacity)
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

// stack stuff
StackPtr create()
{
    // creates the stack
    StackPtr nu = malloc(sizeof(Stack)); // allocate memory for the struct itself
    nu->size = 0;
    nu->capacity = INITIAL_CAPACITY;

    nu->array = calloc(nu->capacity, sizeof(int)); // setting elements in the array to 0

    return nu;
}

void push(StackPtr stack, Node *c)
{
    // inserts to the head of stack
    resize_if_full(stack);
    size_t i;
    for (i = stack->size++; i > 0; --i)
    {
        // shifts all elements towards the end by 1 index;
        stack->array[i] = stack->array[i - 1];
    }
    stack->array[0] = c;
}

Node *peek(StackPtr stack)
{
    return stack->array[0];
}

Node *pop(StackPtr stack)
{
    // removes the head and returns the first value
    Node *head_char = stack->array[0];
    for (size_t i = 0; i < stack->size; ++i)
    {
        stack->array[i] = stack->array[i + 1];
    }
    stack->size--;

    return head_char;
}

void resize_if_full(StackPtr stack)
{
    if (stack->size == stack->capacity)
    {
        stack->capacity *= 2;
        stack->array = realloc(stack->array, stack->capacity * sizeof(int)); // `capacity` is like the number of elements. we need to multiply by the sizeof(int) to get the true number of bytes that need to be allocateted
    }
}

// void print(StackPtr stack)
// {
//     // shows stack
//     for (size_t i = 0; i < stack->size; ++i)
//     {
//         printf("%c, ", stack->array[i]);
//     }
//     puts("END");
// }

void clear(StackPtr stack)
{
    // deletes all nodes in the stack
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
    // stack->array = realloc(stack->array, stack->capacity * sizeof(char));
}

void showArray(int arr[], size_t size)
{
    // prints the array to screen
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}