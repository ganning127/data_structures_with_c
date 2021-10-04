#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char key;          // value
    struct node *next; // pointer to the next element
} Node;
typedef Node *NodePtr;

typedef struct queue
{
    NodePtr start;
    NodePtr end;
} Queue;
typedef Queue *QueuePtr;

QueuePtr create();
void push(QueuePtr queue, char c);
void print(QueuePtr queue);
char pop(QueuePtr queue);
char peek(QueuePtr queue);
void clear(QueuePtr queue);

int main(void)
{
    // i don't know why it says we lost 16 bytes when there are 5 mallocs and 5 frees
    QueuePtr q = create();
    push(q, 'A');
    push(q, 'B');
    push(q, 'D');

    printf("Current Queue: ");
    print(q);

    puts("");

    printf("Popped: %c\n", pop(q));
    printf("After popping Queue: ");
    print(q);
    puts("");

    printf("Clearing Queue...\n");
    clear(q);

    printf("After cleaning Queue: ");
    print(q);

    puts("");

    printf("adding 'E' to queue...\n");
    push(q, 'E');

    printf("Ending Queue: ");
    print(q);

    printf("clearing queue...\n");
    clear(q);

    free(q);
    return 0;
}

QueuePtr create()
{
    QueuePtr new_queue = malloc(sizeof(Queue));
    new_queue->start = NULL;
    new_queue->end = NULL;
    return new_queue;
}
void push(QueuePtr queue, char c)
{
    NodePtr nu = malloc(sizeof(Node));
    nu->key = c;
    nu->next = NULL;

    if (queue->end == NULL)
    {
        queue->start = nu;
        queue->end = nu;
    }

    queue->end->next = nu;
    queue->end = nu;
}

char pop(QueuePtr queue)
{
    NodePtr head_node = queue->start;
    char head_char = head_node->key;

    queue->start = head_node->next;
    free(head_node);

    return head_char;
}

char peek(QueuePtr queue)
{
    return queue->start->key;
}

void print(QueuePtr queue)
{
    if (queue->start == queue->end && queue->start != NULL)
    {
        printf("%c -> ", queue->start->key);
        puts("END");
    }
    else if (queue->start != NULL)
    {
        NodePtr node = queue->start;
        while (node != NULL)
        {
            printf("%c -> ", node->key);
            node = node->next;
        }
        puts("END");
    }
    else
        puts("The queue is empty.");
}

void clear(QueuePtr queue)
{
    if (queue->start == queue->end && queue->start != NULL)
    {
        // there is only one node in the list
        free(queue->start);
    }
    else if (queue->start != NULL)
    {
        // destroy the rest of the list
        queue->start = queue->start->next;

        clear(queue);
        free(queue->start); // free the memory created in malloc
    }
    queue->start = queue->end = NULL;
}