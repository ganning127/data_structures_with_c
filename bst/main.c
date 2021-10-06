#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int key;
    struct node *left;
    struct node *right;

} Node;

typedef Node *NodePtr;

void print_bst(NodePtr bst);
void insert_bst(NodePtr *bstPtr, int key);
void destroy_bst(NodePtr *bstPtr);
void delete_bst(NodePtr *bstPtr, int key);

int main(void)
{
    NodePtr bst = NULL; // we do not need to keep track of how many elements there are, only need a pointer to the first node
    insert_bst(&bst, 46);
    insert_bst(&bst, 100);
    insert_bst(&bst, 6);
    insert_bst(&bst, 4);
    insert_bst(&bst, 3);
    print_bst(bst);
    destroy_bst(&bst);
}

void insert_bst(NodePtr *bstPtr, int key)
{
    NodePtr bst = *bstPtr;
    if (bst == NULL)
    {
        // we have gotten to an empty space, insert here
        NodePtr node = malloc(sizeof(Node));
        node->key = key;
        node->left = node->right = NULL;
        *bstPtr = node; // bstPtr is a pointer to the node. we can't change the node itself because it is a local variable
    }
    else
    {
        if (bst->key > key)
            insert_bst(&(bst->left), key);
        else
            insert_bst(&(bst->right), key);
    }
}

void print_bst(NodePtr bst)
{
    static unsigned int depth = 0; // this line only runs once
    if (bst == NULL)
        return;
    ++depth;
    print_bst(bst->right);
    --depth;

    for (unsigned int i = 0; i < depth; ++i)
        printf("  ");

    printf("%d\n", bst->key);
    ++depth;
    print_bst(bst->left);
    --depth;
}

void destroy_bst(NodePtr *bstPtr)
{
    NodePtr bst = *bstPtr;
    if (bst != NULL)
    {
        destroy_bst(&(bst->left));
        destroy_bst(&(bst->right));
        free(bst);
        *bstPtr = NULL;
    }
}

void delete_bst(NodePtr *bstPtr, int key)
{
    NodePtr bst = *bstPtr;

    if (bst == NULL)
        return;

    if (bst->key > key)
        delete_bst(&(bst->left), key);
    else if (bst->key < key)
        delete_bst(&(bst->right), key);
    else
    {
        // node has been found
        // has no children
        NodePtr newPtr;
        // has one child
        if (bst->left != NULL && bst->right != NULL)
        {
            // children
        }
        else
        {
            // no children or one child
            newPtr = bst->left != NULL ? bst->left : bst->right;
        }

        *bstPtr = newPtr;
        free(bst);
    }
}

// go down to the right subtree, and go left all the way (closest value to the top node)
//      move the leftmost node to the pos of the removed element
//
// go down to the left subtree, and go right all the way (closest value to the top node)