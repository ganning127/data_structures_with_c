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
NodePtr merge_bst(NodePtr treeA, NodePtr treeB);
int *bst_to_list(NodePtr tree);
int *bst_merge_lists(int *listA, int *listB, size_t sizeA, size_t sizeB);
int *bst_to_list_w_size(NodePtr tree, size_t size);
NodePtr bst_list_to_tree_w_size(int *list, size_t size);

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
    insert_bst(&bst, 3);
    insert_bst(&bst, 6);
    insert_bst(&bst, 1);
    insert_bst(&bst, 42);
    insert_bst(&bst, 100);

    print_bst(bst);

    NodePtr merged = merge_bst(bst, bst);

    puts("-----------");
    print_bst(merged);

    puts("");
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

    if (bst == NULL)
        return 0;
    return 1 + size_bst(bst->left) + size_bst(bst->right);
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

int *bst_to_list(NodePtr tree)
{
    static int *list = NULL;
    if (tree == NULL)
        return NULL;

    size_t size = 0;
    if (list == NULL)
    {
        // allocate space for list
        // code only runs when at the root node
        size = size_bst(tree);
        list = calloc(size, sizeof(int));
    }
    bst_to_list(tree->left);
    *list = tree->key;
    ++list; // increment index of list
    bst_to_list(tree->right);

    if (size != 0)
    {
        int *out = list - size; // beginning of the array and copy the list
        list = NULL;
        return out;
    }
    else
        return NULL;
}

int *bst_to_list_w_size(NodePtr tree, size_t size)
{
    static int *list = NULL;
    if (tree == NULL)
    {
        return NULL;
    }

    // creating the list and freeing memory
    if (list == NULL)
    {
        list = calloc(size, sizeof(int));
    }

    bst_to_list_w_size(tree->left, 0);
    *list++ = tree->key; // add key to the list, then increment to the next index

    //++list;
    // why increment list value? because just goes to next index
    bst_to_list_w_size(tree->right, 0);

    // We use the 0 as a flag to say that we aren't done yet. If we have 0, its still in a recursive function call. !=0 would mean that we are at the original fucntion call, or the end
    if (size != 0)
    {
        int *out = list - size;
        list = NULL;
        return out;
    }
    else
        return NULL;
}

NodePtr merge_bst(NodePtr treeA, NodePtr treeB)
{
    /*
        merge tree a and b
        a -> list a
        b -> list b

        merged = merge(a, b)

        merge:
            go through both trees at same time.
            compare elements from each and take the smaller
            from the tree that you took the element from, move the pointer to the next node
        merged -> tree
    */
    size_t sizeA = size_bst(treeA);
    size_t sizeB = size_bst(treeB);
    int *listA = bst_to_list_w_size(treeA, sizeA);
    int *listB = bst_to_list_w_size(treeB, sizeB);

    int *merged = bst_merge_lists(listA, listB, sizeA, sizeB);

    NodePtr tree = bst_list_to_tree_w_size(merged, sizeA + sizeB);
    free(listA);
    free(listB);
    free(merged);
    return tree;
}

int *bst_merge_lists(int *listA, int *listB, size_t sizeA, size_t sizeB)
{
    int *merged = calloc(sizeA + sizeB, sizeof(int));
    size_t i = 0, j = 0;

    while (i < sizeA && j < sizeB)
    {
        if (listA[i] < listB[j])
        {
            merged[i + j] = listA[i];
            ++i;
        }
        else
        {
            merged[i + j] = listB[j];
            ++j;
        }
    }

    // one of the lists are done
    for (; i < sizeA; ++i)
        merged[i + j] = listA[i];
    for (; j < sizeA; ++i)
        merged[i + j] = listB[j];

    return merged;
}

/*
    printing out BST in level order:
        - https://www.google.com/search?q=binary+search+tree&sxsrf=AOaemvIXiGaEpHJGXa2h8gDt3zVr2Yi2IA:1633962273097&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjcufTmx8LzAhXydd8KHWzJDDcQ_AUoAXoECAEQAw&biw=890&bih=1041&dpr=2#imgrc=0oeRvnU5P6AIoM
    output: 8, 3, 1, 6, 4, 7, 10, 14, 13
*/

NodePtr bst_list_to_tree_w_size(int *list, size_t size)
{
    if (size == 0)
        return NULL;

    NodePtr root = malloc(sizeof(Node));
    root->key = list[size / 2];
    root->left = bst_list_to_tree_w_size(list, size / 2);
    root->right = bst_list_to_tree_w_size(list + size / 2 + 1, (size - 1) / 2);

    return root;
}