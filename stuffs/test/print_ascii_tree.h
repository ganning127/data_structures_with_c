#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFINITY (1 << 20)
#define MAX_HEIGHT 1000

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
} Node;
typedef Node *NodePtr;

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

extern NodePtr make_empty(NodePtr t);
extern NodePtr insert(int value, NodePtr t);
extern void print_ascii_tree(NodePtr t);