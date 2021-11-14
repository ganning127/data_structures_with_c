#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 8

typedef struct hash_node
{
    char *key;
    int value;
    struct hash_node *next;
} HNode;

typedef struct arraylist_strings
{
    char **array;    // declared as pointer so we don't need to specify size
    size_t size;     // how many elements its currently holding
    size_t capacity; // how many elements it can hold
} ArrayListStrings;

typedef struct arraylist_nodes
{
    HNode **array;
    size_t size;
    size_t capacity;
} ArrayListNodes;

void resize(ArrayListNodes *);
ArrayListStrings *arls_create();
ArrayListNodes *arln_create();
size_t hash(char *str, size_t size);
void arls_destroy(ArrayListStrings **listPtr);
void arln_destroy(ArrayListNodes **listPtr);
void arln_insert(ArrayListNodes *list, char *key, int value);
int arln_get(ArrayListNodes *list, char *key);

int main(void)
{
    ArrayListStrings *sList = arls_create();
    ArrayListNodes *nList = arln_create();

    arln_insert(nList, "ganning", 1);
    arln_insert(nList, "asdfasdf", 2);
    int value = arln_get(nList, "asdfasdf");

    printf("key found: %d\n", value);

    arls_destroy(&sList);
    arln_destroy(&nList);
    free(nList);
    free(sList);
    return 0;
}

void resize(ArrayListNodes *list)
{
    size_t new_size = list->capacity * 2; // double size of the array
    HNode **new_array = (HNode **)malloc(sizeof(HNode *) * new_size);

    for (size_t i = 0; i < new_size; i++)
    {
        new_array[i] = NULL; // go through each node and set it to NULL
    }

    for (size_t i = 0; i < list->capacity; i++)
    {
        HNode *curr = list->array[i]; // get the current node
        while (curr != NULL)
        {
            size_t index = hash(curr->key, new_size); // get the index of the node in the new array
            HNode *next = curr->next;
            curr->next = new_array[index];
            new_array[index] = curr;
            curr = next;
        }
    }
    free(list->array); // free memory of old array
    list->array = new_array;
    list->capacity = new_size;
}

int arln_get(ArrayListNodes *list, char *key)
{
    size_t index = hash(key, list->capacity);
    HNode *node = list->array[index];
    int key_found = 0;

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            return node->value;
        }
        node = node->next;
    }
    printf("key: %s was not found, returning -1.\n", key);
    return -1;
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
        list->array[index] = nu; // insert to beg of linked list
        nu->next = current;
    }

    list->size++;

    if (list->size > list->capacity * 0.667)
        resize(list);
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

ArrayListStrings *arls_create()
{
    ArrayListStrings *list = malloc(sizeof(ArrayListStrings));
    list->size = 0;
    list->capacity = INITIAL_SIZE;
    list->array = calloc(sizeof(char *), INITIAL_SIZE);
    return list;
}

ArrayListNodes *arln_create()
{
    ArrayListNodes *list = malloc(sizeof(ArrayListNodes));
    list->size = 0;
    list->capacity = INITIAL_SIZE;
    list->array = calloc(sizeof(HNode *), INITIAL_SIZE);
    // set all the pointers to NULL
    for (size_t i = 0; i < list->capacity; i++)
    {
        list->array[i] = NULL;
    }
    return list;
}

void arls_destroy(ArrayListStrings **listPtr)
{
    ArrayListStrings *list = *listPtr;
    for (size_t i = 0; i < list->size; ++i)
    {

        free(list->array[i]);
    }
    free(list->array);
    free(list);
    *listPtr = NULL;
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
}

void arln_destroy(ArrayListNodes **listPtr)
{
    ArrayListNodes *list = *listPtr;
    for (size_t i = 0; i < list->size; ++i)
    {
        lldestroy(&(list->array[i]));
        free(list->array[i]);
    }
    free(list->array);
    free(list);
    *listPtr = NULL;
}

/*
    Struct Node {
        String string;
        node *next;
    }

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
        - loadFactor = numElements / arraySize

*/