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

HeapPtr heap_create(void);                                  // create a new heap
size_t heap_parent(size_t index);                           // get parent index
size_t heap_left(size_t index);                             // get left child index
size_t heap_right(size_t index);                            // get right child index
void heap_print(HeapPtr heap);                              // print heap
void heap_destroy(HeapPtr *heapPtr);                        // destroy heap
void heap_insert(HeapPtr heap, int key);                    // insert key into heap
void heap_bubble(HeapPtr heap, size_t index);               // bubble up
void heap_sift(HeapPtr heap, size_t index);                 // sift down
void heap_resize_if_full(HeapPtr heap);                     // resize if heap is full
void heap_delete_better(HeapPtr heap, int key);             // delete root node
void heap_swap(HeapPtr heap, size_t index1, size_t index2); // swap two nodes
void heap_delete(HeapPtr heap, int key);                    // delete node at index

void heap_queue_push(QueuePtr queue, size_t index); // push index into queue
size_t heap_queue_pop(QueuePtr queue);              // pop index from queue; return -1 if queue is empty

int main(void)
{
    HeapPtr heap = heap_create();
    heap_insert(heap, 42);
    heap_insert(heap, 11);
    heap_insert(heap, 9);
    heap_insert(heap, 23);
    heap_insert(heap, 314);
    heap_print(heap);

    // heap_delete(heap, 9);

    printf("\n");
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

void heap_insert(HeapPtr heap, int key)
{
    heap_resize_if_full(heap);
    heap->array[heap->size] = key; // size-1 is the element of the prev last one
    heap_bubble(heap, heap->size);
    heap->size++;
}
void heap_delete_better(HeapPtr heap, int key)
{

    // find the key
    // swap the last element with the key
    // bubble down the key
    // decrement size

    for (size_t i = 0; i < heap->size; i++)
    {
        if (heap->array[i] == key)
        {
            {
                heap_swap(heap, i, heap->size - 1);
                heap_sift(heap, i + 1);
            }
        }
    }
    heap->size--;
}

void heap_delete(HeapPtr heap, int key)
{
    QueuePtr queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;

    //
}