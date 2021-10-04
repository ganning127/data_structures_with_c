#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 8

typedef struct stack
{
    char *array;     // declared as pointer so we don't need to specify size
    size_t size;     // how many elements its currently holding
    size_t capacity; // how many elements it can hold
} Stack;
typedef Stack *StackPtr;

void resize_if_full(StackPtr list);
StackPtr create();
void push(StackPtr stack, char c);
void print(StackPtr stack);
char pop(StackPtr stack);
char peek(StackPtr stack);
void clear(StackPtr stack);
void destroy(StackPtr stack);
void showArray(int arr[], size_t size);

int main(void)
{
    StackPtr s = create();
    push(s, 'A');
    push(s, 'B');
    push(s, 'C');

    printf("original stack: ");
    print(s);

    puts("");

    printf("popped: %c\n", pop(s));
    printf("peeking: %c\n", peek(s));
    printf("after pop and peeking stack: ");
    print(s);

    puts("");

    printf("clearing stack...\n");
    clear(s);
    printf("after clearing stack: ");
    print(s);

    puts("");
    printf("adding 'D' and 'E' to stack...\n");
    push(s, 'D');
    push(s, 'E');
    printf("after adding more letters stack: ");
    print(s);

    puts("");
    printf("clearing stack...\n");
    clear(s);
    print(s);

    destroy(s); // freeing all memory
}

StackPtr create()
{
    StackPtr nu = malloc(sizeof(Stack)); // allocate memory for the struct itself
    nu->size = 0;
    nu->capacity = INITIAL_CAPACITY;

    nu->array = calloc(nu->capacity, sizeof(char)); // setting elements in the array to 0

    return nu;
}

void push(StackPtr stack, char c)
{
    resize_if_full(stack);
    size_t i;
    for (i = stack->size++; i > 0; --i)
    {
        // shifts all elements towards the end by 1 index;
        stack->array[i] = stack->array[i - 1];
    }
    stack->array[0] = c;
}

char peek(StackPtr stack)
{
    return stack->array[0];
}

char pop(StackPtr stack)
{
    // removes the head
    char head_char = stack->array[0];
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
        stack->array = realloc(stack->array, stack->capacity * sizeof(char)); // `capacity` is like the number of elements. we need to multiply by the sizeof(int) to get the true number of bytes that need to be allocateted
    }
}

void print(StackPtr stack)
{
    for (size_t i = 0; i < stack->size; ++i)
    {
        printf("%c, ", stack->array[i]);
    }
    puts("END");
}

void clear(StackPtr stack)
{
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
    stack->array = realloc(stack->array, stack->capacity * sizeof(char));
}

void destroy(StackPtr stack)
{
    free(stack->array);
    free(stack);
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