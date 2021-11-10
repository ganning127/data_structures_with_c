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
void heap_delete_better(HeapPtr heap, int key);             // extra function that I have that deletes a node
void heap_swap(HeapPtr heap, size_t index1, size_t index2); // swap two nodes
void heap_delete(HeapPtr heap, int key);                    // delete node at index

void heap_queue_push(QueuePtr queue, size_t index); // push index into queue
size_t heap_queue_pop(QueuePtr queue);              // pop head from queue
size_t heap_find(HeapPtr heap, int key);            // find index of key in heap; return heap->sive if key not found
void heap_queue_clear(QueuePtr queue);              // clear queue
void heap_print_in_order(HeapPtr heap);             // print heap in order
void heapify(int arr[], size_t size);               // heapify array
void heap_sort(int arr[], size_t size);             // sort array
void showArray(int arr[], size_t size);

int main(void)
{
    HeapPtr heap = heap_create();
    heap_insert(heap, 42);
    heap_insert(heap, 11);
    heap_insert(heap, 9);
    heap_insert(heap, 23);
    heap_insert(heap, 314);
    heap_insert(heap, 1000);

    // test cases
    puts("Original Heap");
    heap_print(heap);

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

    // look at current node. if not key were are looking for:
    // append its two children to it
    // keep popping things off the head and push to the tail of the queue
    // if we find the key, we can just pop it off the queue

    size_t index = heap_find(heap, key);
    if (index < heap->size)
    {
        heap_swap(heap, index, heap->size - 1);
        heap->size--;

        if (index > 0 && (heap->array[index] > heap->array[heap_parent(index)]))
            heap_bubble(heap, index);
        else
            heap_sift(heap, index);
    }
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

    printf("size: %zu\n", size);
    size_t starting_index = heap_parent(size - 1); // start from the parent of the last node. everything after this is already a heap because they have no children, so they must obey the max heap property.

    for (size_t index = starting_index; index > 0; --index)
        heap_array_sift(arr, index, size);

    heap_array_sift(arr, 0, size);
    showArray(arr, size);
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

void heap_queue_push(QueuePtr queue, size_t index)
{
    QNodePtr new_node = malloc(sizeof(QNode));
    new_node->index = index;
    new_node->next = NULL;

    if (queue->head == NULL)
    {
        queue->head = new_node; // if queue is empty, set head to new node
        queue->tail = new_node; // if queue is empty, set tail to new node
    }
    else
    {
        queue->tail->next = new_node; // if queue is not empty, set tail's next to new node
        queue->tail = new_node;       // set tail to new node
    }
}

size_t heap_find(HeapPtr heap, int key)
{
    // returns the index of the key
    // if key is not in the heap, returns heap->size
    static Queue queue = {NULL, NULL}; // we don't need to use the queue outside this function.

    if (queue.head == NULL)
    {
        if (heap->array[0] == key)
            return 0;
        else if (heap->array[0] < key)
            return heap->size; // not in the array since the key is greater than the root node
        else
        {
            heap_queue_push(&queue, 0);
            return heap_find(heap, key);
        }
    }
    else
    {
        size_t index = heap_queue_pop(&queue);
        size_t left = heap_left(index);
        size_t right = left + 1;

        if (left < heap->size)
        {
            // child must exist
            if (heap->array[left] == key)
            {
                heap_queue_clear(&queue);
                return left;
            }
            else if (heap->array[left])
                heap_queue_push(&queue, left);

            if (right < heap->size)
            {
                if (heap->array[right] == key)
                {
                    heap_queue_clear(&queue);
                    return right;
                }
                else if (heap->array[right] > key)
                    heap_queue_push(&queue, right);
            }
            else
            {
                heap_queue_clear(&queue);
                return heap->size;
            }

            return heap_find(heap, key);
        }
        else
        {
            heap_queue_clear(&queue); // stop checking when we find a node with no children
            return heap->size;
        }
    }
}

void heap_queue_clear(QueuePtr queue)
{
    QNodePtr current = queue->head;
    while (current != NULL)
    {
        QNodePtr temp = current;
        current = current->next;
        free(temp);
    }
    queue->head = NULL;
}

size_t heap_queue_pop(QueuePtr queue)
{
    size_t index = queue->head->index;
    QNodePtr temp = queue->head;
    queue->head = queue->head->next;
    free(temp);
    return index;
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