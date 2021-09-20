#include <stdio.h>
#include <stdlib.h>

/*
Linked lists:
    - Each element in the array points to the next one
    - Can't access elements randomly, can only be accessed sequentially
    - As long as we keep track of the first node, we can access the entire list
    Search time: O(n)
    Add / Delete: O(1) ... constant
*/

typedef struct node
{
    int key;           // value
    struct node *next; // pointer to the next element
} Node;

typedef Node *NodePtr;

void llinsert(NodePtr *list, int key);
void llprint(NodePtr node);
void lldestroy(NodePtr *list);
void llremove(NodePtr *list, int key);

int main(void)
{
    // WORKS EXCEPT CANT DELTE FIRST ELEMENT
    Node *list = NULL; // will be replaced when we insert items into linked list
    llinsert(&list, 42);
    llinsert(&list, 5);
    llinsert(&list, 12);
    llinsert(&list, 54);
    llinsert(&list, 2);

    llprint(list);

    llremove(&list, 42);
    llremove(&list, 5);
    llremove(&list, 12);
    llremove(&list, 54);
    llremove(&list, 2);

    llprint(list);
    lldestroy(&list);

    // printf("list: %p\n", list);

    return 0;
}

void llremove(NodePtr *list, int key)
{
    NodePtr node = *list; // current node

    if (node->key == key)
    {
        *list = node->next;
        free(node);
    }
    else if (node->next == NULL)
        printf("Node `%d` was not found in linked list list\n", key);
    else if (node->next->key == key)
    {
        // where the element belongs is here
        NodePtr delete_node = node->next;
        node->next = node->next->next;

        // node->next = (node->next)->next;
        free(delete_node);
    }
    else
    {
        llremove(&(node->next), key); // node was not found, so call func again
    }
}

void llinsert(NodePtr *list, int key)
{
    // `list` is the memory addr of the pointer to the next node in the list (memory addr of `next`)

    // need to use pointer pointer because we need to change where pointers before element is pointing to when we insert
    // need to point to the new node that was inserted, b/c the old beginning is no longer the beg anymore

    NodePtr node = *list;
    if (node == NULL || node->key >= key)
    {
        // have new node point to the next element
        // Node nu = {key, node};
        NodePtr nu = malloc(sizeof(Node)); // returns a pointer to the allocated memory
        // for every malloc, you ALWAYS need to free it
        nu->key = key;
        nu->next = node;

        // change prev node point to the inserted node
        *list = nu;
    }
    else
        llinsert(&(node->next), key); // node was not found, so call func again
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

void lldestroy(NodePtr *list)
{
    NodePtr node = *list;
    if (node != NULL)
    {
        // destroy the rest of the list
        lldestroy(&(node->next));
        free(node);   // free the memory created in malloc
        *list = NULL; // empty list
    }
}