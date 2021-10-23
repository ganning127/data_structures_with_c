#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 1;

typedef struct node
{
    int key;
    size_t index; // index number in the arraylist
} Node;

typedef struct arraylist
{
    unsigned int capacity; // value
    Node **array;          // array of NodePtr pointers
} ArrayList;
// it should be an array of struct pointers
// each struct should contain key
ArrayList *bst_create();
size_t bst_left_child(size_t index);
size_t bst_right_child(size_t index);
size_t bst_parent_index(size_t index);
void bst_print_level_order(ArrayList *array_list);
void bst_print_in_order(ArrayList *array_list);
void bst_print_tree(ArrayList *array_list);
void print_pointers(ArrayList *list);
void bst_resize(ArrayList *list, unsigned int old_capacity);
void bst_insert(ArrayList *list, int key);
void bst_delete(ArrayList *list, int key);
void bst_destroy(ArrayList **listPtr);
ArrayList *bst_merge(ArrayList *list1, ArrayList *list2);
size_t bst_successor(ArrayList *list, size_t index);

int main(void)
{
    ArrayList *nu = bst_create();
    bst_insert(nu, 4);
    bst_insert(nu, 3);
    bst_insert(nu, 5);
    bst_insert(nu, 2);
    bst_insert(nu, 6);

    ArrayList *nu2 = bst_create();
    bst_insert(nu2, 9);
    bst_insert(nu2, 8);
    bst_insert(nu2, 10);
    bst_insert(nu2, 11);
    bst_insert(nu2, 6);

    ArrayList *nu3 = bst_create();
    bst_insert(nu3, 4);
    bst_insert(nu3, 3);
    bst_insert(nu3, 2);
    bst_insert(nu3, 5);
    bst_insert(nu3, 6);
    bst_insert(nu3, 9);
    bst_insert(nu3, 8);
    bst_insert(nu3, 6);
    bst_insert(nu3, 10);
    bst_insert(nu3, 11);

    puts("original trees");
    puts("*************************");
    puts("--------------------");
    puts("nu");
    puts("--------------------");
    bst_print_tree(nu);

    puts("--------------------");
    puts("nu2");
    puts("--------------------");
    bst_print_tree(nu2);

    puts("--------------------");
    puts("nu3");
    puts("--------------------");
    bst_print_tree(nu3);
    puts("*************************");

    puts("");
    puts("deleting nodes from trees...");
    puts("");
    bst_delete(nu3, 4);
    bst_delete(nu2, 10);
    bst_delete(nu, 6);

    puts("modified trees");
    puts("*************************");
    puts("--------------------");
    puts("nu");
    puts("--------------------");
    bst_print_tree(nu);

    puts("--------------------");
    puts("nu2");
    puts("--------------------");
    bst_print_tree(nu2);

    puts("--------------------");
    puts("nu3");
    puts("--------------------");
    bst_print_tree(nu3);
    puts("*************************");

    puts("");

    puts("merging trees...");
    puts("*************************");
    ArrayList *merged = bst_merge(nu, nu2);
    puts("--------------------");
    puts("merged");
    puts("--------------------");
    bst_print_tree(merged);
    puts("*************************");

    puts("");
    puts("destroying trees and freeing memory");
    bst_destroy(&nu);
    bst_destroy(&nu2);
    bst_destroy(&nu3);
    bst_destroy(&merged);

    free(nu);
    free(nu2);
    free(nu3);
    free(merged);
    return 0;
}

void bst_delete(ArrayList *list, int key)
{
    // if no children nodes, just delete current node
    // if one children node, join the child node to the parent node
    // if two children nodes, find the successor node and replace the current node with the successor node

    // find the node to be deleted
    size_t node_index = 0;

    for (size_t i = 0; i < list->capacity; i++)
    {
        if (list->array[i] == NULL)
            continue;
        else if (list->array[i]->key == key)
        {
            // printf("list key: %d, key: %d\n", list->array[i]->key, key);
            node_index = i;
            break;
        }
    }

    // printf("node_index: %zu\n", node_index);

    size_t left_child = bst_left_child(node_index);
    size_t right_child = bst_right_child(node_index);

    Node *temp = list->array[node_index];
    if ((left_child < list->capacity && right_child < list->capacity) && (list->array[left_child] != NULL && list->array[right_child] != NULL))
    {
        // two children nodes
        size_t successor_index = bst_successor(list, right_child);
        size_t successor_index_right_child = bst_right_child(successor_index);

        list->array[node_index] = list->array[successor_index];
        list->array[node_index]->index = node_index; // update the index of the successor node to the index of the node that it is replacing
        list->array[successor_index] = list->array[successor_index_right_child];
        list->array[successor_index_right_child] = NULL;
    }
    else if (left_child < list->capacity && list->array[left_child] != NULL)
    {
        // one child node
        list->array[node_index] = list->array[left_child];
        list->array[node_index]->index = node_index;
        list->array[left_child] = NULL;
    }
    else if (right_child < list->capacity && list->array[right_child] != NULL)
    {
        // one child node
        // puts("right child");
        list->array[node_index] = list->array[right_child];
        list->array[node_index]->index = node_index;
        list->array[right_child] = NULL;
    }
    else
    {
        // no children nodes
        list->array[node_index] = NULL;
    }
    free(temp);
}

size_t bst_successor(ArrayList *list, size_t index)
{

    while ((index < list->capacity))
    {

        index = bst_left_child(index);
        if (index >= list->capacity || list->array[index] == NULL)
        {
            index = bst_parent_index(index);
            break;
        }
    }

    return index;
}

ArrayList *bst_merge(ArrayList *list1, ArrayList *list2)
{
    ArrayList *merged_list = bst_create();
    int i = 0;
    int j = 0;
    while (i < list1->capacity && j < list2->capacity)
    {
        if (list1->array[i] != NULL && list2->array[j] != NULL)
        {
            if (list1->array[i]->key < list2->array[j]->key)
            {
                // printf("insert from list1: %d\n", list1->array[i]->key);
                bst_insert(merged_list, list1->array[i]->key);
                i++;
            }
            else
            {
                // printf("insert from list2: %d\n", list2->array[i]->key);
                bst_insert(merged_list, list2->array[j]->key);
                j++;
            }
        }
        else if (list1->array[i] == NULL)
        {
            i++;
        }
        else if (list2->array[j] == NULL)
        {
            j++;
        }
    }
    while (i < list1->capacity)
    {
        if (list1->array[i] != NULL)
        {
            bst_insert(merged_list, list1->array[i]->key);
        }
        ++i;
    }
    while (j < list2->capacity)
    {
        if (list2->array[j] != NULL)
        {
            bst_insert(merged_list, list2->array[j]->key);
        }
        j++;
    }
    return merged_list;
}

void bst_destroy(ArrayList **listPtr)
{
    ArrayList *list = *listPtr;
    for (int i = 0; i < list->capacity; i++)
    {
        free(list->array[i]);
    }
    free(list->array);
    free(list);
    *listPtr = NULL;
}

// void bst_delete(ArrayList *list, int key)
// {
//     // delete node from binary tree
//     for (size_t i = 0; i < list->capacity; i++)
//     {
//         if (list->array[i] == NULL)
//             continue;
//         else if (list->array[i]->key == key)
//         {
//             free(list->array[i]);
//             list->array[i] = NULL;
//         }
//     }
// }

void bst_print_tree_helper(ArrayList *array_list, Node *node)
{
    static unsigned int depth = 0;
    if (node == NULL)
        return;
    ++depth;
    size_t right_index = bst_right_child(node->index);
    if (right_index < array_list->capacity)
    {
        bst_print_tree_helper(array_list, array_list->array[right_index]);
    }
    --depth;
    for (unsigned int i = 0; i < depth; ++i)
    {
        printf("  ");
    }

    printf("%d\n", node->key);
    ++depth;
    size_t left_index = bst_left_child(node->index);
    if (left_index < array_list->capacity)
    {
        bst_print_tree_helper(array_list, array_list->array[left_index]);
    }
    --depth;
}

void bst_print_tree(ArrayList *array_list)
{
    // print binary tree
    bst_print_tree_helper(array_list, array_list->array[0]);
}

void bst_in_order_helper(ArrayList *array_list, Node *node)
{

    if (node == NULL)
    {
        return;
    }

    size_t left_index = bst_left_child(node->index);
    size_t right_index = bst_right_child(node->index);

    if (left_index < array_list->capacity)
        bst_in_order_helper(array_list, array_list->array[left_index]);

    printf("%d ", node->key);

    if (right_index < array_list->capacity)
        bst_in_order_helper(array_list, array_list->array[right_index]);
}

void bst_print_in_order(ArrayList *array_list)
{
    bst_in_order_helper(array_list, array_list->array[0]);
    puts("");
}

void print_pointers(ArrayList *list)
{
    for (size_t i = 0; i < list->capacity; ++i)
        printf("%p ", list->array[i]);

    puts("");
}
void bst_insert(ArrayList *list, int key)
{
    // printf("key called: %d\n", key);
    size_t index_insert = 0;

    while (list->array[index_insert] != NULL)
    {
        if (key < list->array[index_insert]->key)
        {
            // look at left child
            index_insert = bst_left_child(index_insert);
        }
        else if (key >= list->array[index_insert]->key)
        {
            // look at right child
            index_insert = bst_right_child(index_insert);
        }
        if (index_insert >= list->capacity)
        {
            bst_resize(list, list->capacity);
        }
    }

    // insert here
    Node *nu = malloc(sizeof(Node));
    nu->key = key;
    nu->index = index_insert;
    list->array[index_insert] = nu;
}

ArrayList *bst_create()
{
    ArrayList *nu = malloc(sizeof(ArrayList)); // allocate memory for the struct itself
    nu->capacity = INITIAL_CAPACITY;

    nu->array = calloc(nu->capacity, sizeof(Node *)); // setting elements in the array to 0

    return nu;
}

size_t bst_left_child(size_t index) { return 2 * index + 1; }
size_t bst_right_child(size_t index) { return 2 * index + 2; }
size_t bst_parent_index(size_t index)
{
    if (index % 2 == 1)
        return (index - 1) / 2;

    return (index - 2) / 2;
}

void bst_print_level_order(ArrayList *array_list)
{
    for (size_t i = 0; i < array_list->capacity; ++i)
    {
        if (array_list->array[i] == NULL)
            printf("N ");
        else
            printf("%d ", (array_list->array[i])->key);
    }
    printf("\n");
}

void bst_resize(ArrayList *list, unsigned int old_capacity)
{
    list->capacity = old_capacity * 2 + 1;                               // double the capacity
    list->array = realloc(list->array, list->capacity * sizeof(Node *)); // reallocate memory for the array

    for (size_t i = old_capacity; i < list->capacity; ++i)
        list->array[i] = NULL; // set the new elements to NULL
}
/*
    Implementation: Store nodes of the binary stree in level order in the arraylist

    capacity: 2^depth - 1
    left(index): 2(index) + 1
    right(index): 2(index) + 2
    parent(index):
        if (index % 2 == 1)
            parent_index = (index-1) / 2
        else if (index % 2 == 0)
            parent_index = (index-2) / 2

    we resize bst when we need to add another depth

    new_capacity(old_capacity): 2*old_capacity + 1
*/
