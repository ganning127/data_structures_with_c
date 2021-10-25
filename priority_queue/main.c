/*
    max heap: parent is greater than its children


    resize() {
        new_capacity = capacity * 2 + 1
    }

    delete() {
        log(n)
        delete root node
        move last element (furthest to bottom at right) to the new root node
        sift root node to where it is supposed to be
    }

    implementing:
        - binary tree represented by arraylist
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
    size_t size;
    size_t capacity;
    int *array;
} Heap;
typedef Heap *HeapPtr;

HeapPtr heap_create(void);
size_t heap_parent(size_t index);
size_t heap_left(size_t index);
size_t heap_right(size_t index);
void heap_print(HeapPtr heap);
void heap_destroy(HeapPtr *heapPtr);
void heap_insert(HeapPtr heap, int key);
void heap_bubble(HeapPtr heap, size_t index);
void heap_sift(HeapPtr heap, size_t index);
void heap_resize_if_full(HeapPtr heap);
void heap_swap(HeapPtr heap, size_t index1, size_t index2);

int main(void)
{
    HeapPtr heap = heap_create();
    heap_print(heap);
    heap_destroy(&heap);
    free(heap);
    return 0;
}

HeapPtr heap_create(void)
{
    HeapPtr heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = 1;
    heap->array = calloc(heap->capacity, sizeof(int));
    return heap;
}

void heap_print(HeapPtr heap)
{
    static unsigned int depth = 0;
    static size_t index = 0;

    if (index >= heap->size)
        return;

    index = heap_right(index);
    ++depth;
    heap_print(heap);
    --depth;
    index = heap_parent(index);

    // given a certain index, the depth is Math.floor(log2(index+1))
    for (unsigned int i = 0; i < depth; ++i)
        printf("  ");
    printf("%d\n", heap->array[index]); // print key out of heap

    index = heap_left(index);
    ++depth;
    heap_print(heap);
    --depth;
    index = heap_parent(index);
}

void heap_destroy(HeapPtr *heapPtr)
{
    HeapPtr heap = *heapPtr;
    free(heap->array);
    free(heap);
    *heapPtr = NULL;
}

void heap_bubble(HeapPtr heap, size_t index)
{
    if (index == 0)
        return;

    size_t parent_index = heap_parent(index);

    if (heap->array[index] > heap->array[parent_index])
    {
        // int temp = heap->array[parent_index];
        // heap->array[parent_index] = heap->array[index];
        // heap->array[index] = temp;
        // heap_bubble(heap, parent_index);

        heap_swap(heap, index, parent_index);
        heap_bubble(heap, parent_index);
    }
}

void heap_sift(HeapPtr heap, size_t index)
{
    if (index >= heap->size) // anything >= size is the equivilent of NULL
        return;

    size_t left_index = heap_left(index);
    size_t right_index = heap_right(index);
}

// helpers
size_t heap_left(size_t index)
{
    return 2 * index + 1;
}

size_t heap_right(size_t index)
{
    return 2 * index + 2;
}

size_t heap_parent(size_t index)
{
    return (index - 1) / 2;
}

void heap_swap(HeapPtr heap, size_t index1, size_t index2)
{
    int temp = heap->array[index1];
    heap->array[index1] = heap->array[index2];
    heap->array[index2] = temp;
}
aee void resize_if_full(Heap *list)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(int)); // `capacity` is like the number of elements. we need to multiply by the sizeof(int) to get the true number of bytes that need to be allocateted
    }
}