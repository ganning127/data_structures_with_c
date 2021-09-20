#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next; // pointer of type node, that points to the next eleemnt
} node;

node *createLinkedList(int n);
void displayList(node *head);

int main(void)
{
    int n = 5;
    node *HEAD = NULL; // set pointer to a node instance equal to NULL, bc there are no element in linked list yet
    // HEAD is just a varoable name holding the pointer
    HEAD = createLinkedList(n);
    displayList(HEAD);
    return 0;
}

node *createLinkedList(int n)
{
    // `n` is the number of nodes we want

    int i = 0;
    node *head = NULL; // address of first node
    node *temp = NULL; // a individual node placed into linked list
    node *p = NULL;    // iterate through list

    for (i = 0; i < n; ++i)
    {

        // create individual isolated node
        temp = (node *)malloc(sizeof(node));
        printf("\nEnter the data %d: ", i);
        scanf("%d", &(temp->data));
        temp->next = NULL;

        if (head == NULL)
            head = temp; // if list is currently empty, then make temp as first node
        else
        {
            p = head;
            while (p->next != NULL)
                p = p->next;

            p->next = temp;
        }
    }
    return head;
}

void displayList(node *head)
{
    if (head != NULL)
    {
        printf("%d -> ", head->data);
        displayList(head->next);
    }
}