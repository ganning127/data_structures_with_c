#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;           // value
    struct node *next; // pointer to the next element
} Node;

typedef Node *NodePtr;

void q_push(NodePtr *list, int key);
void q_pop(NodePtr *list);
int q_peek(NodePtr *list);
void llprint(NodePtr node);

int main(void)
{
    Node *list = NULL;
    q_push(&list, 1);
    q_push(&list, 2);
    q_pop(&list);
    q_push(&list, 3);
    q_push(&list, 1124142);
    printf("peeking: %d\n", q_peek(&list));

    llprint(list);
    return 0;
}

void q_push(NodePtr *list, int key)
{
    NodePtr node = *list;
    if (node == NULL)
    {
        // insert here
        NodePtr nu = malloc(sizeof(Node));
        nu->key = key;
        nu->next = NULL;
        *list = nu;
    }
    else
        q_push(&(node->next), key);
}

void q_pop(NodePtr *list)
{
    NodePtr node = *list;
    if (node != NULL)
    {
        *list = node->next;
        free(node);
    }
    else
        printf("There are no nodes in this list.\n");
}

int q_peek(NodePtr *list)
{
    NodePtr node = *list;
    if (node != NULL)
        return (*list)->key;
    else
    {
        printf("There are no nodes in this list.\n");
        return -1;
    }
}

void llprint(NodePtr node)
{
    // base case is when node is NULL
    if (node != NULL)
    {
        printf("%d -> ", node->key);
        llprint(node->next);
    }
    else
        puts("END");
}