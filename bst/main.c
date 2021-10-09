#include <stdlib.h>
#include <stdio.h>

/*
    For all functions except size, destroy, print (since they are O(n)): The time complexity of the tree depends on whether or not the tree is balanced.

    size, destroy, print:
        Best, Worst, Avg: O(n)

    Worst case is always O(n)

    More elaborate comments are in the below functions
*/

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
NodePtr *successor_bst(NodePtr *treePtr);
size_t size_bst(NodePtr bst);
//
int main(void)
{
    NodePtr bst = NULL; // we do not need to keep track of how many elements there are, only need a pointer to the first node
    // insert_bst(&bst, 42);
    // insert_bst(&bst, 100);
    // insert_bst(&bst, 6);
    // insert_bst(&bst, 4);
    // insert_bst(&bst, 3);
    // insert_bst(&bst, 7);
    // insert_bst(&bst, 100);
    insert_bst(&bst, 1);
    insert_bst(&bst, 2);
    insert_bst(&bst, 3);
    insert_bst(&bst, 4);
    insert_bst(&bst, 5);
    insert_bst(&bst, 6);

    print_bst(bst);
    delete_bst(&bst, 42);
    puts("-------");

    printf("size: %zu\n", size_bst(bst));
    puts("-------");
    print_bst(bst);
    destroy_bst(&bst);
}

void insert_bst(NodePtr *bstPtr, int key)
{
    /*
        Avg: O(log(n))
            Testing for (bst == NULL)
            Recursive call with half nodes

        Worst: O(n)
            When there are n elements in the BST, and there are also n levels, and therefore, and search would take n traversals. For example, inserting (1, 2, 3, 4, 5), in that order, would lead to worst case

        Best: O(log(n))
            When the BST is balanced, the time complexity is O(log(n)), which is the best case senario. Doubling the number of elements in the tree only adds one iteration, which is the definition of a log(n) time complexity. 
    
    */

    static unsigned int count = 0;
    NodePtr bst = *bstPtr;
    if (bst == NULL)
    {
        // we have gotten to an empty space, insert here
        ++count;
        NodePtr node = malloc(sizeof(Node));
        node->key = key;
        node->left = node->right = NULL;
        *bstPtr = node; // bstPtr is a pointer to the node. we can't change the node itself because it is a local variable
    }
    else
    {
        count++;
        if (bst->key > key)
            insert_bst(&(bst->left), key);
        else
            insert_bst(&(bst->right), key);
    }
}

void print_bst(NodePtr bst)
{
    /*
        Avg, Best, Worst: O(n)
            You need to go through each node in order to print it, resulting in a time complexity of O(n). 
    */

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

size_t size_bst(NodePtr bst)
{
    /*
        Avg, Best, Worst: O(n)
            In the size function, you need to go through each node, which leads to a time complexity of O(n), because you need a new iteration for each elment. 
    */

    static unsigned int count = 0;
    if (bst == NULL)
    {
        ++count;
        printf("count: %u\n", count);
        return 0;
    }
    else
    {
        ++count;
        printf("count: %u\n", count);
        return 1 + size_bst(bst->left) + size_bst(bst->right);
    }
}

void destroy_bst(NodePtr *bstPtr)
{
    /*
        Avg, Best, Worst: O(n)
            You need to go through each node in order to destroy the and free each node, resulting in a time complexity of O(n).
    */
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
    /*
        Avg: O(log(n))
            Testing for (bst == NULL)
            Recursive call with half nodes
            Deleting the node
    
        Worst: O(n)
            When the BST is unabalanced, you might need to go through each node in order to find the node that you want to delete, resulting in a time complexity of O(n).

        Best: O(log(n))
            When the BST is balanced, the time complexity is O(log(n)), which is the best case senario. Doubling the number of elements in the tree only adds one iteration, which is the definition of a log(n) time complexity. 

    */
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
            // go down to the right subtree, and go left all the way (closest value to the top node)
            //      move the leftmost node to the pos of the removed element
            //
            // go down to the left subtree, and go right all the way (closest value to the top node)

            NodePtr *successorPtr = successor_bst(&(bst->right)); // left mode node of the right subtree

            newPtr = *successorPtr;        // deref to get successor
            *successorPtr = newPtr->right; // promote the right child to where the deleted node is

            // copy original nodes childrent to successor
            newPtr->right = bst->right;
            newPtr->left = bst->left;
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

NodePtr *successor_bst(NodePtr *treePtr)
{
    NodePtr tree = *treePtr;
    if (tree->left == NULL)
    {
        return treePtr;
    }
    return successor_bst(&(tree->left));
}
