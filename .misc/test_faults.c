#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    char key;          // value
    struct node *next; // pointer to the next element
} Node;

int main(void)
{
    Node *n = malloc(sizeof(Node));
    n->key = 'K';
    n->next = NULL;

    free(n);

    printf("%c\n", n->key);
}
