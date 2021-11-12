#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
    size_t size;
    size_t capacity;
    int *array;
} Heap;
typedef Heap *HeapPtr;

typedef struct qnode
{
    size_t index;
    struct qnode *next;
} QNode;
typedef QNode *QNodePtr;

typedef struct queue
{
    QNodePtr head;
    QNodePtr tail;
} Queue;
typedef Queue *QueuePtr;

// functions needed for priority queue pop and push
HeapPtr priority_queue_create(void);                        // create a new heap
void priority_queue_push(HeapPtr heap, int key);            // insert key into heap
int priority_queue_pop(HeapPtr heap);                       // delete and return root
void heap_sort(int arr[], size_t size);                     // sort array
void heapify(int arr[], size_t size);                       // heapify array
size_t heap_parent(size_t index);                           // get parent index
size_t heap_left(size_t index);                             // get left child index
size_t heap_right(size_t index);                            // get right child index
void heap_destroy(HeapPtr *heapPtr);                        // destroy heap
void heap_bubble(HeapPtr heap, size_t index);               // bubble up
void heap_sift(HeapPtr heap, size_t index);                 // sift down
void heap_resize_if_full(HeapPtr heap);                     // resize if heap is full
void heap_swap(HeapPtr heap, size_t index1, size_t index2); // swap two nodes
void heap_print(HeapPtr heap);                              // print heap
void heap_print_in_order(HeapPtr heap);                     // print heap in order
void showArray(int arr[], size_t size);

int main(void)
{
    /*
        Priority Queue and Heap sort
            - priority_queue_push() is the function that inserts a new node into the heap
            - priority_queue_pop() is the function that deletes the root node and returns its value
            - heap_sort() is the function that sorts the array using heap sort

    */

    // Push and pop to and from the priority queue. While doing so, print out the heap in both array and binary tree format.
    HeapPtr heap = priority_queue_create();
    priority_queue_push(heap, 42);
    priority_queue_push(heap, 11);
    priority_queue_push(heap, 9);
    priority_queue_push(heap, 23);
    priority_queue_push(heap, 314);
    priority_queue_push(heap, 1000);

    // test cases
    puts("Original Heap (tree form)");
    heap_print(heap); // binary tree form
    puts("");
    puts("Original Heap (array form)");
    heap_print_in_order(heap);

    // test cases
    puts("");
    int popped = priority_queue_pop(heap);
    printf("popped: %d\n", popped);

    int popped2 = priority_queue_pop(heap);
    printf("popped2: %d\n", popped2);
    puts("");
    heap_print(heap);

    heap_destroy(&heap);

    puts("--------------------------------");
    size_t length = 10;
    int arr[length];
    for (size_t i = 0; i < length; i++)
    {
        arr[i] = rand() % 100; // random numbers from 1-100
    }
    puts("Original Array");
    showArray(arr, length);

    heap_sort(arr, length);

    puts("");
    puts("Sorted Array");
    showArray(arr, length);
    return 0;
}

HeapPtr priority_queue_create(void)
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

    size_t current_index = index;
    size_t right = heap_right(index);
    index = right;

    ++depth;
    heap_print(heap);
    --depth;
    index = current_index;

    // given a certain index, the depth is Math.floor(log2(index+1))
    for (unsigned int i = 0; i < depth; ++i)
        printf("  ");
    printf("%d\n", heap->array[index]); // print key out of heap

    index = right - 1;
    ++depth;
    heap_print(heap);
    --depth;
    index = current_index;
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
    // used when we insert a new element
    // insert at size, and bubble it up from there
    if (index == 0)
        return;

    size_t parent_index = heap_parent(index);

    if (heap->array[index] > heap->array[parent_index])
    {
        heap_swap(heap, index, parent_index);
        heap_bubble(heap, parent_index);
    }
}

void heap_sift(HeapPtr heap, size_t index)
{
    // used when we delete an element
    // sift down from the root node
    // swap the greatest child with where the node is
    size_t left = heap_left(index);
    if (left >= heap->size)
        return;
    size_t right = left + 1;
    size_t max_child = (right < heap->size && heap->array[right] > heap->array[left]) ? right : left;

    if (heap->array[index] < heap->array[max_child])
    {
        // check if the parent is greater than the child
        heap_swap(heap, index, max_child);
        heap_sift(heap, max_child);
    }
}

void priority_queue_push(HeapPtr heap, int key)
{
    heap_resize_if_full(heap);
    heap->array[heap->size] = key; // size-1 is the element of the prev last one
    heap_bubble(heap, heap->size);
    heap->size++;
}

int priority_queue_pop(HeapPtr heap)
{
    int key = heap->array[0];
    if (heap->size > 0)
    {
        heap_swap(heap, 0, heap->size - 1);
        heap->size--;

        heap_sift(heap, 0);
    }
    return key;
}

void heap_array_sift(int arr[], size_t index, size_t size)
{
    // used when we delete an element
    // sift down from the root node
    // swap the greatest child with where the node is
    size_t left = heap_left(index);
    if (left >= size)
        return;

    size_t right = left + 1;
    size_t max_child = (right < size && arr[right] > arr[left]) ? right : left;

    if (arr[index] < arr[max_child])
    {
        // check if the parent is greater than the child
        int temp = arr[index];
        arr[index] = arr[max_child];
        arr[max_child] = temp;
        heap_array_sift(arr, max_child, size);
    }
}

void heapify(int arr[], size_t size)
{
    // in place heapify array
    // start at the last parent
    // bubble down

    if (size <= 2)
        return;

    size_t starting_index = heap_parent(size - 1); // start from the parent of the last node. everything after this is already a heap because they have no children, so they must obey the max heap property.

    for (size_t index = starting_index; index > 0; --index)
        heap_array_sift(arr, index, size);

    heap_array_sift(arr, 0, size);
}

void heap_sort(int arr[], size_t size)
{
    heapify(arr, size);

    for (size_t i = size - 1; i > 1; --i)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heap_array_sift(arr, 0, i);
    }
    // swap zero and index one
    int temp = arr[0];
    arr[0] = arr[1];
    arr[1] = temp;
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

void heap_resize_if_full(HeapPtr heap)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2 + 1;
        heap->array = realloc(heap->array, heap->capacity * sizeof(int));
    }
}

void heap_print_in_order(HeapPtr heap)
{
    printf("[");
    for (size_t i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->array[i]);
    }
    printf("]\n");
}

void showArray(int arr[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}