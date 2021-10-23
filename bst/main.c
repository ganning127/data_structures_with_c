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

typedef struct queue_node
{
    NodePtr key;             // node in BST
    struct queue_node *next; // pointer to the next element
} QueueNode;
typedef QueueNode *QueueNodePtr;

typedef struct queue
{
    QueueNodePtr start;
    QueueNodePtr end;
} Queue;
typedef Queue *QueuePtr;

QueuePtr create();
void push(QueuePtr queue, NodePtr c);
void print(QueuePtr queue);
NodePtr pop(QueuePtr queue);
NodePtr peek(QueuePtr queue);
void clear(QueuePtr queue);

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
void print_in_level_order(NodePtr bst);

int main(void)
{
    // NodePtr bst = NULL; // we do not need to keep track of how many elements there are, only need a pointer to the first node

    // NodePtr bst1 = NULL;
    // NodePtr bst2 = NULL;

    // puts("bst:");
    // insert_bst(&bst, 3);
    // insert_bst(&bst, 6);
    // insert_bst(&bst, 2);
    // insert_bst(&bst, 1);
    // insert_bst(&bst, 42);
    // insert_bst(&bst, 100);
    // print_bst(bst);
    // print_in_level_order(bst);

    // puts("");
    // puts("bst1:");
    // insert_bst(&bst1, 1);
    // insert_bst(&bst1, 2);
    // insert_bst(&bst1, 3);
    // insert_bst(&bst1, 4);
    // insert_bst(&bst1, 5);
    // insert_bst(&bst1, 6);
    // print_bst(bst1);
    // print_in_level_order(bst1);

    // puts("");
    // puts("bst2:");
    // insert_bst(&bst2, 7);
    // insert_bst(&bst2, 2);
    // insert_bst(&bst2, 1);
    // insert_bst(&bst2, 4);
    // insert_bst(&bst2, 3);
    // insert_bst(&bst2, 6);
    // insert_bst(&bst2, 11);
    // insert_bst(&bst2, 8);
    // insert_bst(&bst2, 13);
    // print_bst(bst2);
    // print_in_level_order(bst2);

    // NodePtr merged = merge_bst(bst, bst1);

    // puts("-------------------");
    // puts("merged: ");
    // print_bst(merged);
    // print_in_level_order(merged);

    // puts("");

    // destroy_bst(&bst);
    // destroy_bst(&bst1);
    // destroy_bst(&bst2);
    // destroy_bst(&merged);
    NodePtr nu = NULL;
    insert_bst(&nu, 4);
    insert_bst(&nu, 3);
    insert_bst(&nu, 5);
    insert_bst(&nu, 2);
    insert_bst(&nu, 6);
    delete_bst(&nu, 4);
    print_bst(nu);
    NodePtr *successor = successor_bst(&(nu->right));
    printf("successor: %d\n", (*successor)->key); // 2
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
    //
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

// QUEUE

QueuePtr create()
{
    // creates a new queue
    QueuePtr new_queue = malloc(sizeof(Queue));
    new_queue->start = NULL;
    new_queue->end = NULL;
    return new_queue;
}

void push(QueuePtr queue, NodePtr c)
{
    // adds element to the end of the queue
    QueueNodePtr nu = malloc(sizeof(Node));
    nu->key = c;
    nu->next = NULL;

    if (queue->end == NULL)
    {
        queue->start = nu;
        queue->end = nu;
        return;
    }

    queue->end->next = nu;
    queue->end = nu;
}

NodePtr pop(QueuePtr queue)
{
    // deletes and returns the head element
    NodePtr head_char = NULL; // in case there isn't a queue made yet

    if (queue->start != NULL)
    {
        QueueNodePtr node = queue->start;
        head_char = node->key;
        if (node->next == NULL)
            queue->start = queue->end = NULL; // there was only one node in the list
        else
            queue->start = node->next; // set prev node to point to next node
        free(node);
    }

    return head_char;
}

NodePtr peek(QueuePtr queue)
{
    // returns the head element
    if (queue->start)
        return queue->start->key;
    return NULL;
}

void llprint(QueueNodePtr node)
{
    // `llprint()` is a helper function that prints
    if (node != NULL)
    {
        printf("%d -> ", node->key->key);
        llprint(node->next);
    }
    else
        puts("END");
}

void print(QueuePtr queue)
{
    if (queue->start == queue->end && queue->start != NULL)
    {
        printf("%d -> ", queue->start->key->key);
        puts("END");
    }
    else if (queue->start != NULL)
    {
        QueueNodePtr node = queue->start;
        llprint(node);
    }
    else
        puts("END");
}

void clear(QueuePtr queue)
{
    // deletes all nodes in the queue
    if (queue->start)
    {
        if (queue->start == queue->end) // only 1 element in the queue
        {
            free(queue->start);
        }
        else // the queue contains multiple elements
        {
            QueueNodePtr node = queue->start;
            QueueNodePtr next;
            for (; node != NULL; node = next)
            {
                next = node->next;
                free(node);
            }
        }
    }
    queue->start = queue->end = NULL;

    // free(queue) to make sure all memory is freed
}

void level_printer(QueuePtr q)
{
    // pop off element
    if (q->start == NULL)
        return;
    NodePtr curr_node = pop(q);
    // print(q);
    printf("%d ", curr_node->key);
    // push left and right nodes
    if (curr_node->left != NULL)
        push(q, curr_node->left);

    if (curr_node->right != NULL)
        push(q, curr_node->right);

    // print popped element

    level_printer(q);
}

void print_in_level_order(NodePtr bst)
{
    if (bst == NULL)
        return;

    QueuePtr q = create();
    push(q, bst);

    level_printer(q);

    clear(q);
    free(q);
    puts("");
}