#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_CAPACITY 1
#define LOAD_FACTOR_MIN 2
#define LOAD_FACTOR_MAX 8

typedef struct hash_node
{
    char *key;
    int value;
    struct hash_node *next;
} HNode;

typedef struct arraylist_nodes
{
    HNode **array;
    size_t keys;
    size_t capacity;
} ArrayListNodes;

void resize(ArrayListNodes *, size_t new_capcity);
ArrayListNodes *arln_create();
size_t hash(char *str, size_t size);
void arln_destroy(ArrayListNodes **listPtr);
void arln_insert(ArrayListNodes *list, char *key, int value);
int arln_get(ArrayListNodes *list, char *key);
void arln_delete(ArrayListNodes *list, char *key);
void showBuckets(ArrayListNodes *list); // for showing which nodes are in the linked list

int main(void)
{
    ArrayListNodes *nList = arln_create();
    arln_insert(nList, "ins1", 1);
    arln_insert(nList, "ins2", 2);
    arln_insert(nList, "ins3", 3);
    arln_insert(nList, "ins4", 4);
    arln_insert(nList, "ins5", 5);
    arln_insert(nList, "ins6", 6);
    arln_insert(nList, "ins7", 7);
    arln_insert(nList, "ins8", 8);
    arln_insert(nList, "ins9", 9);
    arln_insert(nList, "ins10", 10);
    arln_insert(nList, "ins11", 11);
    arln_insert(nList, "ins12", 12);
    arln_insert(nList, "ins13", 13);
    arln_insert(nList, "ins14", 14);
    arln_insert(nList, "ins15", 15);
    arln_insert(nList, "ins16", 16);
    arln_insert(nList, "ins17", 17);
    arln_insert(nList, "ins18", 18);
    arln_insert(nList, "ins19", 19);
    arln_insert(nList, "ins20", 20);

    printf("%d\n", arln_get(nList, "ins1"));
    printf("%d\n", arln_get(nList, "ins2"));
    printf("%d\n", arln_get(nList, "ins3"));
    printf("%d\n", arln_get(nList, "ins4"));
    printf("%d\n", arln_get(nList, "ins5"));
    printf("%d\n", arln_get(nList, "el oh el")); // key will not be found

    arln_delete(nList, "ins1");
    arln_delete(nList, "ins2");
    arln_delete(nList, "ins3");
    arln_delete(nList, "ins4");
    arln_delete(nList, "ins5");
    arln_delete(nList, "ins6");
    arln_delete(nList, "ins7");
    arln_delete(nList, "ins8");
    arln_delete(nList, "ins9");
    arln_delete(nList, "ins10");
    arln_delete(nList, "ins11");
    arln_delete(nList, "ins12");
    arln_delete(nList, "ins13");
    arln_delete(nList, "HELLO"); // key will not be found

    arln_destroy(&nList);

    puts("");

    ArrayListNodes *nList2 = arln_create();
    arln_insert(nList2, "ins1", 1);
    arln_insert(nList2, "ins2", 2);
    arln_insert(nList2, "ins3", 3);
    arln_insert(nList2, "ins4", 4);
    arln_insert(nList2, "ins5", 5);

    puts("--------showing that arln_get() puts nodes at the front of the linked list--------");
    showBuckets(nList2);
    arln_get(nList2, "ins1");

    showBuckets(nList2);

    arln_destroy(&nList2);
    return 0;
}

void resize(ArrayListNodes *list, size_t new_capacity)
{
    HNode **new_array = (HNode **)calloc(sizeof(HNode *), new_capacity);

    for (size_t i = 0; i < list->capacity; i++)
    {
        HNode *curr = list->array[i]; // get the current node
        while (curr != NULL)
        {
            size_t index = hash(curr->key, new_capacity); // get the index of the node in the new array
            HNode *next = curr->next;
            curr->next = new_array[index];
            new_array[index] = curr;
            curr = next;
        }
    }
    free(list->array); // free memory of old array
    list->array = new_array;
    list->capacity = new_capacity;
}

int arln_get(ArrayListNodes *list, char *key)
{
    size_t index = hash(key, list->capacity);
    HNode *node = list->array[index];

    if (strcmp(node->key, key) == 0)
        return node->value; // check if the first node in the linked list is the node that we want

    while (node->next != NULL)
    {
        if (strcmp(node->next->key, key) == 0)
        {
            // move next node to beginning of linked list
            HNode *temp = node->next;
            node->next = temp->next;
            temp->next = list->array[index];
            list->array[index] = temp;

            return temp->value;
        }
        node = node->next;
    }
    printf("key: \"%s\" was not found, returning 0.\n", key);
    return 0;
}

HNode *next_node_is_target(HNode *node, char *key)
{
    while (node->next != NULL)
    {
        if (strcmp(node->next->key, key) == 0)
        {
            return node; // node->next is the target node
        }
        node = node->next;
    }
    return NULL;
}

void arln_insert(ArrayListNodes *list, char *key, int value)
{
    size_t index = hash(key, list->capacity);
    HNode *nu = malloc(sizeof(HNode));
    nu->key = key;
    nu->value = value;
    nu->next = NULL;

    if (list->array[index] == NULL)
    {
        list->array[index] = nu;
    }
    else
    {
        HNode *current = list->array[index];
        if (strcmp(current->key, key) == 0)
        {
            current->value = value; // just update the value
            return;
        }

        HNode *prev_node = next_node_is_target(current, key);
        if (prev_node)
        {
            // move the node to the beginning of linked list
            HNode *temp = prev_node->next;
            prev_node->next = temp->next;
            temp->next = list->array[index];
            list->array[index] = temp;
        }
        else
        {
            // key was not already in linked list
            list->array[index] = nu; // insert to beg of linked list
            nu->next = current;
        }
    }

    list->keys++;

    if (list->keys > list->capacity * LOAD_FACTOR_MAX)
    {
        resize(list, list->capacity * 2);
    }
}

void arln_delete(ArrayListNodes *list, char *key)
{
    size_t index = hash(key, list->capacity);
    HNode *curr = list->array[index];
    HNode *prev = NULL;

    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
        {
            if (prev == NULL)
                list->array[index] = curr->next;
            else
                prev->next = curr->next;
            free(curr);
            list->keys--;

            if (list->keys < list->capacity * LOAD_FACTOR_MIN && list->capacity > 1) // cannot resize to have a list of size 0
            {
                resize(list, list->capacity / 2);
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    // key must not have been found
    printf("key: \"%s\" was not found.\n", key);
}

size_t hash(char *str, size_t size)
{
    // generate a hash value for a string (to index into array)
    size_t hash = 0;
    while (*str != '\0')
    {
        // printf("%c", *str);
        hash = (hash * 31 + *str) % size;
        ++str;
    }

    return hash;
}

ArrayListNodes *arln_create()
{
    ArrayListNodes *list = malloc(sizeof(ArrayListNodes));
    list->keys = 0;
    list->capacity = INITIAL_CAPACITY;
    list->array = calloc(sizeof(HNode *), list->capacity); // automatically initialized to NULL
    return list;
}

void lldestroy(HNode **list)
{
    // delete nodes in the linked list
    HNode *node = *list;
    if (node != NULL)
    {
        // destroy the rest of the list
        lldestroy(&(node->next));
        free(node);   // free the memory created in malloc
        *list = NULL; // empty list
    }
    free(*list); // free the memory created in calloc
    *list = NULL;
}

void arln_destroy(ArrayListNodes **listPtr)
{
    ArrayListNodes *list = *listPtr;
    for (size_t i = 0; i < list->capacity; ++i)
    {
        lldestroy(&(list->array[i]));
        free(list->array[i]);
    }
    free(list->array);
    free(list);
    *listPtr = NULL;
}

void llprint(HNode *node)
{
    // base case is when node is NULL
    if (node != NULL)
    {
        printf("%s -> ", node->key);
        llprint(node->next);
    }
    else
        puts("END");
}

void showBuckets(ArrayListNodes *list)
{
    for (size_t i = 0; i < list->capacity; i++)
    {
        if (list->array[i] != NULL)
        {
            printf("Bucket %zu: ", i);
            llprint(list->array[i]);
        }
    }
}

/*

    Hashing: process of turning a key into a hash keys.
        - a collision occurs when two keys have the same hash keys
        - this makes two things map to the same hash value

    HashFunction():
        hash = 0;
        for each char in string:
            hash = (hash * 31 + char) %M // M is the array size // 31 because that is what java uses
        return hash

    if there are two different keys with the same hash value, then there is a collision
    CollisionResolution():
        - array of linked lists
        - each linked list is a bucket

    Reize HashMap:
        - double the size of the array
        - rehash all the keys in the old array into the new array
        - update the hash function to use the new array size

    LoadFactor
        - we do NOT want to wait until hash_map is full to resize it
        - we want to resize it when the load factor is greater than 2/3 or 0.6666667
        - loadFactor = nodes / arraySize
        - NOT the number of buckets used

*/
