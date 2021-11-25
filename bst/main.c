#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define INFINITY 999999
#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
int print_next;
int gap = 3;

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;

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

typedef struct printTreeNode
{
    struct printTreeNode *left, *right;
    // length of the edge from this node to its children
    int edge_length;
    int height;
    int lablen;
    int parent_dir;
    char label[11];
} printTreeNode;
typedef printTreeNode *printTreeNodePtr;

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
void print_bst_vertical(NodePtr t);

int main(void)
{

    NodePtr nu3 = NULL;
    insert_bst(&nu3, 3);
    insert_bst(&nu3, 1);
    insert_bst(&nu3, 2);
    insert_bst(&nu3, 4);
    insert_bst(&nu3, 5);
    insert_bst(&nu3, 6);
    insert_bst(&nu3, 7);

    puts("Sideways tree");
    print_bst(nu3);

    puts("---------");
    puts("vertically printed");
    print_bst_vertical(nu3);

    destroy_bst(&nu3);
    free(nu3);
}
void insert_bst(NodePtr *bstPtr, int key)
{
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
    for (; j < sizeA; ++j)
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

//// asdfasdfsa

int MIN(int X, int Y)
{
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y)
{
    return ((X) > (Y)) ? (X) : (Y);
}

printTreeNodePtr build_vertical_tree_recursive(NodePtr t)
{
    printTreeNodePtr node;

    if (t == NULL)
        return NULL;

    node = malloc(sizeof(printTreeNode));
    node->left = build_vertical_tree_recursive(t->left);
    node->right = build_vertical_tree_recursive(t->right);

    if (node->left != NULL)
    {
        node->left->parent_dir = -1;
    }

    if (node->right != NULL)
    {
        node->right->parent_dir = 1;
    }

    sprintf(node->label, "%d", t->key);
    node->lablen = strlen(node->label);

    return node;
}
printTreeNodePtr build_vertical_tree(NodePtr t)
{
    printTreeNodePtr node;
    if (t == NULL)
        return NULL;
    node = build_vertical_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}

// prints vertical tree for given Node structure
void compute_lprofile(printTreeNodePtr node, int x, int y)
{
    int i, isleft;
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->left != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(printTreeNodePtr node, int x, int y)
{
    int i, notleft;
    if (node == NULL)
        return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->right != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

// This function fills in the edge_length and
// height fields of the specified tree
void compute_edge_lengths(printTreeNodePtr node)
{
    int h, hmin, i, delta;
    if (node == NULL)
        return;
    compute_edge_lengths(node->left);
    compute_edge_lengths(node->right);

    /* first fill in the edge_length of node */
    if (node->right == NULL && node->left == NULL)
    {
        node->edge_length = 0;
    }
    else
    {
        if (node->left != NULL)
        {
            for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
            {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->left, 0, 0);
            hmin = node->left->height;
        }
        else
        {
            hmin = 0;
        }
        if (node->right != NULL)
        {
            for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
            {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->right, 0, 0);
            hmin = MIN(node->right->height, hmin);
        }
        else
        {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++)
        {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        // If the node has two children of height 1, then we allow the
        // two leaves to be within 1, instead of 2
        if (((node->left != NULL && node->left->height == 1) ||
             (node->right != NULL && node->right->height == 1)) &&
            delta > 4)
        {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    // now fill in the height of node
    h = 1;
    if (node->left != NULL)
    {
        h = MAX(node->left->height + node->edge_length + 1, h);
    }
    if (node->right != NULL)
    {
        h = MAX(node->right->height + node->edge_length + 1, h);
    }
    node->height = h;
}

// This function prints the given level of the given tree, assuming
// that the node has the given x cordinate.
void print_level(printTreeNodePtr node, int x, int level)
{
    int i, isleft;
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    if (level == 0)
    {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++)
        {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->lablen;
    }
    else if (node->edge_length >= level)
    {
        if (node->left != NULL)
        {
            for (i = 0; i < (x - print_next - (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != NULL)
        {
            for (i = 0; i < (x - print_next + (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else
    {
        print_level(node->left,
                    x - node->edge_length - 1,
                    level - node->edge_length - 1);
        print_level(node->right,
                    x + node->edge_length + 1,
                    level - node->edge_length - 1);
    }
}

void free_vertical_tree(printTreeNodePtr node)
{
    if (node == NULL)
        return;
    free_vertical_tree(node->left);
    free_vertical_tree(node->right);
    free(node);
}

// prints vertical tree for given Node structure
void print_bst_vertical(NodePtr t)
{
    printTreeNodePtr proot;
    int xmin, i;
    if (t == NULL)
        return;
    proot = build_vertical_tree(t);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++)
    {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    free_vertical_tree(proot);
}
