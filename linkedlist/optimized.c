#include <stdio.h>
#include <stdlib.h>
#define SAFE_FREE(p) \
    {                \
        if (p)       \
            free(p); \
        p = NULL;    \
    }

typedef struct node
{
    int key;           // value
    struct node *next; // pointer to the next element
} Node;

typedef Node *NodePtr;

int main(void)
{
    return 0;
}

Node *ll_insert_end(NodePtr list, NodePtr new_node)
{
    NodePtr traversal_node;

    if (list == NULL)
        return new_node;
    for (traversal_node = list; traversal_node->next != NULL; traversal_node = traversal_node->next)
        ;

    traversal_node->next = new_node; // at the end of the list b/c of for loop
    return list;
}