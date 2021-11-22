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

typedef struct asciinode
{
    struct asciinode *left, *right;

    // length of the edge from this node to its children
    int edge_length;

    int height;

    int lablen;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    // max supported unit32 in dec, 10 digits max
    char label[11];
} Asciinode;
typedef Asciinode *AsciinodePtr;
